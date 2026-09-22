#include "JohnConway.h"
#include "../fsm/Action.h"
#include "../fsm/AgentContext.h"
#include "../fsm/Condition.h"

#include <SDL3/SDL_log.h>

#include <iostream>
#include <stdexcept>

// The four Conway rules as machine parts:
//   underpopulation / overpopulation -> conditions that leave Alive
//   reproduction                     -> condition that leaves Dead
//   survival is implicit: no transition firing means the stay actions run.
//
// Where the data lives (read this before touching anything):
//   - the persistent state of a cell is one bit in the world grid;
//   - the Alive/Dead State objects below are shared behavior nodes, not storage:
//     every cell runs the same two nodes, they hold nothing per-cell;
//   - per-update info (position, isAlive, aliveNeighbors) travels in the AgentContext.

// begin solution
namespace conway {
  class Underpopulation : public Condition {
  public:
    bool Test(const AgentContext& context) override {
      return context.aliveNeighbors < 2;
    }
  };

  class Overpopulation : public Condition {
  public:
    bool Test(const AgentContext& context) override {
      return context.aliveNeighbors > 3;
    }
  };

  class Reproduction : public Condition {
  public:
    bool Test(const AgentContext& context) override {
      return context.aliveNeighbors == 3;
    }
  };

  class DieAction : public Action {
  public:
    void Execute(const AgentContext& context) override {
      context.world.SetNext(context.position, false);
    }
  };

  class BornAction : public Action {
  public:
    void Execute(const AgentContext& context) override {
      context.world.SetNext(context.position, true);
    }
  };

  class StayAliveAction : public Action {
  public:
    void Execute(const AgentContext& context) override {
      context.world.SetNext(context.position, context.world.Get(context.position));
    }
  };

  class StayDeadAction : public Action {
  public:
    void Execute(const AgentContext& context) override {
      context.world.SetNext(context.position, context.world.Get(context.position));
    }
  };
}  // namespace conway

// end solution

JohnConway::JohnConway() {
  using namespace conway;

  alive = std::make_shared<State>("Alive");
  dead = std::make_shared<State>("Dead");

  const auto die = std::make_shared<DieAction>();
  const auto born = std::make_shared<BornAction>();

  // todo: add transitions and actions for alive, dead. example:
  //   alive->AddTransition(std::make_shared<Underpopulation>(), dead, {die});
  //   dead->AddAction(std::make_shared<StayDeadAction>());

  // begin solution
  // note: log instead of throw - the constructor runs at app startup and at
  // every fixture load; throwing here would kill the process before it runs.
  alive->AddTransition(std::make_shared<Overpopulation>(), dead, {die});
  dead->AddTransition(std::make_shared<Reproduction>(), alive, {born});
  alive->AddTransition(std::make_shared<Underpopulation>(), dead, {die});
  alive->AddAction(std::make_shared<StayAliveAction>());
  dead->AddAction(std::make_shared<StayDeadAction>());
  // end solution
}

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // relevant functions:
  //   world.Height() and world.Width() to get the world dimensions,
  //   world.Get() reads the CURRENT generation, world.SetNext() writes the NEXT one
  // Build one context per cell and let the machine decide: conditions read the
  // current generation through the context, actions write the next one.
  //
  // note: the double buffering does NOT happen here. Your actions only write
  // the next buffer via SetNext; whoever drives the simulation (the demo app's
  // Manager::step or the life-tests runner) calls world.SwapBuffers() right
  // AFTER this function returns. Never call SwapBuffers from inside a rule.
  // begin solution
  for (int y = 0; y < world.Height(); ++y) {
    for (int x = 0; x < world.Width(); ++x) {
      AgentContext context{world, {x, y}, world.Get({x, y}), CountNeighbors(world, {x, y})};
      machine.SetCurrent(context.isAlive ? alive : dead);
      machine.Update(context);
    }
  }
  // end solution
  // todo: implement
  //for (int x = 0; x < world.SideSize(); x++) {
  //  for (int y = 0; y < world.SideSize(); y++) {
  //    int neighbors = CountNeighbors(world, {x, y});
  //    if (world.Get({x, y})) {
  //      if (neighbors < 2 || neighbors > 3) {
  //        world.SetNext({x, y}, false);
  //      } else {
  //        world.SetNext({x, y}, true);
  //      }
  //    } else {
  //      if (neighbors == 3) {
  //        world.SetNext({x, y}, true);
  //      }
  //    }
  //  }
  //}
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // Eight neighbors
  Point2D checkedPoint = point;
  int neighbors = 0;
  checkedPoint.x--;
  checkedPoint.y--;
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      if (x == 1 && y == 1) continue;
      Point2D addPoint = {x, y};
      if (world.Get(checkedPoint + addPoint))
      {
        neighbors++;
      }
    }
  }

  return neighbors;
}
