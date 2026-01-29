
// file name: court_nw.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note: Bicornv
// bug(s):
// to-do:

inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "park.h"

/* Room 27 */

static object bicornbrn;

create_room()
{
set_short("In the Courtyard");
set_long("This is the north end of the"
        +" large courtyard.  The high stone walls rise up"
        +" beside you, and finely-spaced cobblestones"
        +" cover the ground.  The luminescence of the strange"
        +" light source above illuminates this place with an"
        +" almost-eerie light.  You can follow the wall to the"
        +" northeast or southwest, or cross to the eastern side"
        +" of the courtyard by moving southeast.\n");

AE(PK+"court_w","southwest",0);
AE(PK+"court_n","northeast",0);
AE(PK+"court_e","southeast",0);

add_prop(ROOM_I_LIGHT,1);IN

STDCOURT


  reset_room();
}

reset_room()
{
  if (!bicornbrn)
   {
      bicornbrn = clone_object(PK+"mon/bicornbrn");
      bicornbrn->move_living("M", this_object());
    }
}
