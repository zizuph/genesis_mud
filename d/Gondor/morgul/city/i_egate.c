#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("The Morgul Road is entering the city here through a " +
    "giant archway under the city wall. To the east, you can see the " +
    "two large wings of the gate. The wide walls are made from large boulders of dark rock. " +
    "To both sides of the gate some steps lead into guardrooms inside " +
    "the walls.");
  set_road(9);
  set_short_desc("inside the Mordor Gate in Minas Morgul");
  set_side("east");

  add_exit(MORGUL_DIR + "city/gateh3","north","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/gateh4","south","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/mmr5","west","@@check_exit",2);
    add_morgul_road();
  add_item(({"archway","arch"}), BSN(
    "The giant archway runs through the city wall. Only here, inside the " +
    "archway can you see the true width of the citywalls, exceeding 40 feet " +
    "at the base. High above you, you can see the large stone blocks which " +
    "have been expertly fitted together to form the arch in the wall. "));
  add_item(({"wall","walls","city walls","city wall"}), BSN(
    "You are standing in an archway running through the city walls. Only here, " +
    "inside the walls you can see the true width of the walls, exceeding 40 feet " +
    "at the base. "));
  add_item(({"boulder","boulders","rock"}), BSN(
    "You marvel at the work of some long dead craftsmen who hewed " +
    "these giant boulders from hard rock and expertly fitted them " +
    "together so that you can hardly make any cracks between them to " +
    "build these mighty walls. "));
  add_item(({"step","steps","stone slabs","slabs"}), BSN(
    "Just three stone slabs leading up into the guardrooms. "));

    clone_object(MORGUL_DIR + "city/mordorgate2.c")->move(TO);
    call_other(MORGUL_DIR + "city/mmr3","short");
    call_other(MORGUL_DIR + "city/wall/wall01","short");
    call_other(MORGUL_DIR + "city/wall/wall08","short");
}

