
// file name: court_w.c
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

/* Room 24 */

create_room()
{
set_short("In the Courtyard");
set_long("You stand at the west side of"
        +" a large, spacious cobblestone courtyard.  It has been"
        +" kept in excellent shape.  The courtyard is bounded by tall"
        +" stone walls, and the cobbles in the floor are evenly"
        +" spaced and smoothed over.  This looks like a meeting"
        +" place of some sort.  You may"
        +" follow the stone wall to the northeast or southeast,"
        +" cross the courtyard to the east, or leave by"
        +" going northwest.\n");

AE(PK+"w_path10","northwest",0);
AE(PK+"court_nw","northeast",0);
AE(PK+"court_e","east",0);
AE(PK+"court_s","southeast",0);

add_prop(ROOM_I_LIGHT,1);IN

STDCOURT

}
