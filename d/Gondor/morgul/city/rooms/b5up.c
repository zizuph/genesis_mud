#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void    reset_room();
static object *humans = allocate(2 + random(2));

public void
create_morgul_room()
{
    set_extraline("From the furniture here, you conclude that these are the " +
    "quarters of humans serving in the Morgul army. Stairs are leading down " +
    "to the ground floor of the house. In the east wall there is a window " +
    "overlooking the street.");
  add_item(({"stairs","stair"}), BSN(
    "Stairs are leading down to the ground floor of the building. "));
  add_item(({"furniture"}), BSN(
    "There are beds along all walls except the east wall, and in the middle " +
    "of the room a wooden table stands, surrounded by several chairs. "));
  add_item(({"beds","cots","bed","cot"}), BSN(
    "These are simple wooden beds, a wooden frame with a mattress inside. On the " +
    "beds are thick woollen blankets which look like they can easily keep the " +
    "occupants of the beds warm, even in winter. You count three beds, one along " +
    "each wall, except for the east wall. "));
  add_item(({"table"}), BSN(
    "A large wooden table is standing in the middle of the room. On the table " +
    "top lies a grey table-cover made from linen. "));
  add_item(({"chair", "chairs"}), BSN(
    "Around the table you can see almost a five wooden chairs. They look simple, " +
    "comfortable, and sturdy. "));
  add_item(({"street","window","windows"}), 
    "@@exa_window|"+
    "Through the window you can look out onto narrow Dark Street and the Red " +
    "Eye Inn which is just across the street from this building. |"+
    MORGUL_DIR+"city/darkstr3@@");

    set_road(5);
    set_side("north");
    add_prop(ROOM_I_LIGHT,1);

    add_exit(MORGUL_DIR + "city/barrack5", "down",
        "@@stairs|down the flight of stairs leading to the ground floor@@",1);
    add_exit("/d/Gondor/clubs/anghoth/room/pub_board_room", "west",  0, 0);


    reset_room();
}

public void
reset_room()
{
    set_alarm(30.0 + rnd() * 60.0, 0.0,
        &clone_npcs(humans, MORGUL_DIR + "npc/ithil_officer", 60.0));
}

