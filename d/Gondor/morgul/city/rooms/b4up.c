#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void    reset_room();

static object  general;

public void
create_morgul_room()
{
    set_extraline("The furniture is very comfortable here, you conclude that " +
    "the officer living here must be in the highest ranks of the Morgul army. Stairs are leading down " +
    "to the ground floor of the house. In the east wall there is a window " +
    "overlooking the street.");
  add_item(({"stairs","stair"}), BSN(
    "Stairs are leading down to the ground floor of the building. "));
  add_item(({"furniture"}), BSN(
    "In the middle of the room, there is a large table, surrounded by several chairs. " +
    "Close to the northern wall, there is a desk. Behind a curtain in front of the " +
    "wall opposite to the window you can see a bed. "));
  add_item(({"curtain","bed","cot"}), BSN(
    "Behind the curtain you can see a large bed. It is made of a wooden frame " +
    "filled with a thick mattress. On it lie several thick woollen blankets and " +
    "some pillows."));
  add_item(({"table"}), BSN(
    "A large wooden table is standing in the middle of the room. On the table " +
    "top lies a white table-cover made from linen. "));
  add_item(({"chair", "chairs"}), BSN(
    "Around the table you can see almost a five wooden chairs. They seem to have been " +
    "made with great care, but little skill. Nevertheless, they look very comfortable. "));
  add_item(({"desk"}), BSN(
    "The desk is standing close to the northern wall of the room. Its top is empty."));
  add_item(({"street","window","windows"}), 
    "@@exa_window|"+
    "Through the window you can look out onto narrow Dark Street and the post " +
    "office which is just across the street from this building. |"+
    MORGUL_DIR+"city/darkstr4@@");

  set_road(9);
  set_short_desc("in the living quarters of an officer");
  set_side("east");

  add_exit(MORGUL_DIR + "city/barrack4","down",
        "@@stairs|down the flight of stairs leading to the ground floor@@",1);
  add_prop(ROOM_I_LIGHT,1);
  add_prop(ROOM_I_INSIDE,1);

  reset_room();
}

public void
reset_room()
{
    if (objectp(general))
        return;

    general = clone_npc(general, MORGUL_DIR + "npc/ithil_officer");
    general->set_name("general");
    general->set_short("general");
    general->set_pshort("generals");
    general->remove_adj(general->query_adjs()[0]);
    general->set_long(general->query_long() + 
      "He also looks like he is used to giving commands, and being obeyed!\n");
}

