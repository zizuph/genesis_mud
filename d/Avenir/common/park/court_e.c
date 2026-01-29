
// file name: court_e.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note: Bicornbrn
// bug(s):
// to-do:

inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "park.h"

/* Room 27 */

static object bicorna;
static object bicornbrn;
static object bicornblk;
create_room()
{
set_short("In the Courtyard");
set_long("This is the far eastern end of a large,"
        +" spacious courtyard.  High stone walls rise up beside you"
        +" and encircle the area.  The ground here is finely paved"
        +" with evenly-spaced cobblestones, smoothed over with fine"
        +" craftsman's skills.  You may follow the walls to the northeast"
        +" and southwest, cross to the far side of the courtyard"
        +" by going northwest or west, or leave the area by"
        +" heading east.\n");

AE(PK+"court_ne","northeast",0);
AE(PK+"court_s","southwest",0);
AE(PK+"court_w","west",0);
AE(PK+"e_path9","east",0);
AE(PK+"court_nw","northwest",0);

add_prop(ROOM_I_LIGHT,1);IN

STDCOURT

  reset_room();
}

reset_room()
{
    if (!bicorna)
    {
        bicorna = clone_object(PK+"mon/bicorna");
        bicorna->move_living("M", this_object());
    }
    
    if (!bicornblk)
    {
        bicornblk = clone_object(PK+"mon/bicornblk");
        bicornblk->move_living("M", this_object());
    }
}

