inherit "/d/Gondor/anorien/nimrais/quest/wall.c";
#include "dirdefs.h".
#include "/d/Gondor/defs.h"

#define UP_ROOM      "wall2"
#define DOWN_ROOM    "base"

create_room()
{
  area = "White Mountains";
  where = "a steep mountain slope";
  extraline = "You are here at the top of the slope, and at the foot of " +
    "a cliff rising almost vertically for hundreds of feet above you. " +
    "But the rock wall is full of cracks that an experienced climber " +
    "might use to climb to a ledge visible above your head. " +
    "Looking down, you can see the steep slope falling down " +
    "back into the valley. " +
    "You might be able to climb up here, or you can climb down. ";
  add_item(({"ledge"}), BSN(
    "About 25 feet above your head you can make out a small ledge " +
    "running almost horizontally across the rock wall. If " +
    "you managed to reach it, you might be able to continue " +
    "further from there. "));
  up_room = THIS_DIR + UP_ROOM;
  down_room = THIS_DIR + DOWN_ROOM;
  make_the_room();
}
