
// file name: court_ne.c
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

/* Room 30 */

create_room()
{
set_short("In the Courtyard");
set_long("You are standing beside the tall stone"
        +" wall that outlines the boundaries of this large,"
        +" spacious cobblestone courtyard.  The area all around"
        +" you is clean and clear of any intrusion or obstacle."
        +"  You may follow the wall from here to the north or"
        +" southwests.\n");

AE(PK+"court_n","north",0);
AE(PK+"court_e","southwest",0);

add_prop(ROOM_I_LIGHT,1);IN

STDCOURT

}
