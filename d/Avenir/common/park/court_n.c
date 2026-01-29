
// file name: court_n.c
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

/* Room 29 */

create_room()
{
set_short("In the Courtyard");
set_long("You stand in the far northeastern corner of"
        +" the large, oddly-shaped courtyard.  The cries of"
        +" various birds and beasts reach your ears through the still"
        +" air.  You can follow the high stone wall which surrounds"
        +" the courtyard to the southwest and south.\n");

AE(PK+"court_nw","southwest",0);
AE(PK+"court_ne","south",0);

add_prop(ROOM_I_LIGHT,1);IN

STDCOURT

}
