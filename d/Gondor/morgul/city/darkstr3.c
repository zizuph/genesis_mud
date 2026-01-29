#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("This is a dark and narrow street somewhere close " +
    "to the Great Tower. To the west you can see a run-down house, to " +
    "the east there seems to be an inn. The street continues " +
    "north to the city wall, while to the south it runs into the " +
    "Morgul Road.");
  set_road(3);
  set_side("north");

    clone_object(MORGUL_DIR + "city/doors/inndoorout")->move(TO);
    add_tower();
    add_house();
  add_item(({"wall","city wall"}), BSN(
    "All you can see from here is that some way to the north this " +
    "street seems to end at the foot of the northern city wall. "));
  add_item(({"morgul road"}), BSN(
    "To the south, you can see the broad Morgul Road running from " +
    "the Great Tower eastward to the Mordor Gate. "));
  add_exit(MORGUL_DIR + "city/darkstr4","north","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/mmr4","south","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/barrack5","west","@@check_exit",1);
}
