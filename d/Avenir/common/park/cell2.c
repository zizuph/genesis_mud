// file name: cell2.c
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

/* Room 8 */


create_room()
{
set_short("A small cell");
set_long("This is a square, crumbling cell. On the northwest wall"
	+" once hung a gate, but it has long since rusted away. A warm"
	+" breeze blows in through the doorway, stirring dust and some"
	+" scattered leaves. This place feels very lonely.\n");

        add_prop(ROOM_I_LIGHT,1);
        IN_IN

        AE(PK+"square_rm","northwest",0);

STDCELL

}

