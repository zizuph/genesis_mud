// file name: cell3.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note:
// bug(s):
// to-do:


inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "park.h"

/* Room 12 */


create_room()
{
set_short("A small cell");
set_long("This is a large, age old stone room that may have once"
	+" been used as a holding cell, although it has long since"
	+" passed its usefulness. Thin vines crawl up through the"
	+" stones of the floor, slowly breaking them apart as the"
	+" years go by. A feeling of stale memories resides here, ghosts"
	+" from long ago still haunt the area.\n");

        add_prop(ROOM_I_LIGHT,1);
        IN_IN

AE(PK+"w_path1","south",0);

STDCELL

}

