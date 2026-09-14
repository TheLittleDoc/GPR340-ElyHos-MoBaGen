#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
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
      if (checkedPoint.x + x < 0)
      {
        addPoint.x = world.SideSize() - 1;
      }
      if (checkedPoint.y + y < 0) {
        addPoint.y = world.SideSize() - 1;
      }

      if (checkedPoint.x + x + 1 >= world.SideSize()) {
        addPoint.x = -world.SideSize() + 1;
      }
      if (checkedPoint.y + y + 1 >= world.SideSize()) {
        addPoint.y = -world.SideSize() + 1;
      }

      if (world.Get(checkedPoint + addPoint))
      {
        neighbors++;
      }
    }
  }
  return neighbors;
}
