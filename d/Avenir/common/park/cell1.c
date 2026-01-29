// file name: cell1.c
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

/* Room 7 */


create_room()
{
set_short("A small cell");
set_long("This is a small cell-like room."
        +" The stone walls around you must have once stood high,"
        +" and the gate held strong; now the stone has begun to crumble,"
        +" and the iron gate at the room's entrance is rusted and"
        +" hangs weakly on its age-old hinges. In the distance"
        +" you can hear the cries of the wild birds and beasts that still"
        +" linger on this island."
        +"\n");

add_prop(ROOM_I_LIGHT,1);
IN_IN

AE(PK+"square_rm","southwest",0);

STDCELL

}

