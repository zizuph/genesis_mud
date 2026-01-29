// file name: cell4.c
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

/* Room 17 */


create_room()
{
set_short("A small cell");
set_long("This is a tiny square room made from stone with no"
	+" windows. It seems to have been used as a cell at one time."
	+" The gateway to the southwest had rusted away into nothing,"
	+" and a soft, untouched layer of dust rests on the floor. You"
	+" feel like you are disturbing something with your presence.\n");

        add_prop(ROOM_I_LIGHT,1);
        IN_IN

AE(PK+"w_path5","southwest",0);

STDCELL

}

