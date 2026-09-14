#include "JohnConway.h"
#include <iostream>

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
  for (int x = 0; x < world.SideSize(); x++) {
    for (int y = 0; y < world.SideSize(); y++) {
      int neighbors = CountNeighbors(world, {x, y});
      if (world.Get({x, y})) {
        if (neighbors < 2 || neighbors > 3) {
          world.SetNext({x, y}, false);
        } else {
          world.SetNext({x, y}, true);
        }
      } else {
        if (neighbors == 3) {
          world.SetNext({x, y}, true);
        }
      }
    }
  }
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
