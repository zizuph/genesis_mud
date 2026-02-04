/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* A resting cell in the dormitory part of the guild */
inherit "std/room";

#include <stdproperties.h>

#define OTHER_CELLS ({"cell_n", "cell_e"})
#include "/d/Terel/mecien/valley/guild/cell.h"

create_room()
{
    set_short("Resting cell");
    set_long(
        "It is a resting cell. There is not much here except a bed.\n");
    add_item("bed", "@@my_bed");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
   
    add_exit(PATH + "dormitory",  "north", "@@leave");
    resting = 0;
    reset_room();
}
