inherit "/d/Gondor/anorien/nimrais/quest/wall.c";
#include "dirdefs.h"
#include "/d/Gondor/defs.h"
#include "/sys/ss_types.h"

#define UP_ROOM      "ledge1"
#define DOWN_ROOM    "wall1"

create_room()
{
  area = "White Mountains";
  where = "a mountain wall";
  extraline = "Close above your head, you can see a narrow ledge. " +
    "Climbing up, you might be able to reach it. Or you could climb down the wall again. ";
  up_room = THIS_DIR + UP_ROOM;
  down_room = THIS_DIR + DOWN_ROOM;
  make_the_room();
  add_item(({"ledge"}), BSN(
    "Several feet above you you can see a small ledge running almost " +
    "horizontally across the rock wall. If you can climb up to the " +
    "ledge, you might be able to continue from there. "));
}

