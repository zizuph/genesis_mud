
// file name: court_s.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note: Bicorna
// bug(s):
// to-do:

inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "park.h"

/* Room 25 */
static object bicorna;


create_room()
{
set_short("In the Courtyard");
set_long("This is the south end of the"
        +" large cobblestone courtyard.  You may follow the walls"
        +" to the northeast and northwest.  A nondescript"
        +" hut of deep grey stone sits just to the south of"
        +" here.\n");

AE(PK+"court_w","northwest",0);
AE(PK+"court_e","northeast",0);
AE(PK+"bldg","south",0);

add_prop(ROOM_I_LIGHT,1);IN

STDCOURT
COURTHUT

  reset_room();
}

reset_room()
{
  if (!bicorna)
   {
      bicorna = clone_object(PK+"mon/bicorna");
      bicorna->move_living("M", this_object());
    }
}

