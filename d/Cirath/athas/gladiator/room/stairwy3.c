/* stairwy3.c: Top of staircase: Serpine, 4-24-95. */
#pragma save_binary

inherit "/std/room";
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "defs.h"

void
create_room()
{
    set_short("top of staircase");
    set_long("You are at the top of the stone staircase. The room is dark " +
      "and quiet, as if a separate world from that of the chambers "+
      "below. Extremely detailed carvings grace the walls, and an "+
      "archway leads south to a large chamber.\n");

    add_item(({"carvings", "carving", "wall", "walls"}), "They are images "+
      "of the Gladiators of Athas, serving the King of Tyr in "+
      "bloody games and abroad. Many of them are pictured as "+
      "willingly (and literaly) dying to please him.\n");

    add_item(({"staircase", "stone staircase"}), "For some reason you can "+
      "not hear any of the sounds from below.\n");

    INSIDE

    add_exit(GLAD_ROOM+"stairwy2.c", "down", 0, 1);
    add_exit(GLAD_ROOM+"counrcpt.c", "south", 0, 1);
}
