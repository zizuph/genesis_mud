
 /* Digit 03 JUNE 95 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "defs.h"


void
create_room()
{
    set_short("In a watery room");
    set_long("You are standing in a room in which water is running "+
        "down the walls like a waterfall, and disappears into the floor "+
        "like magic.  There is a beautiful statue made of ice here.  "+
        "The room seems to be lit up by some sort of glow coming from "+
        "inside the statue.  There is a passage leading north from here.\n");

    add_item(({"water","walls"}),"The water seems to appear out of "+
        "nowhere where the ceiling meets the beginning of the walls, "+
        "and disappears mysteriously where the walls meet the floor.  "+
        "It is warm to the touch, and gives the air a refreshing smell.\n");

    add_item(({"beautiful statue","ice statue","statue"}),"The statue "+
        "is of a beautiful female human attired in robes, on her knees "+
        "with her hands held high above her head, as though praying to "+
        "her god.  There is a strange glow eminating from the middle of "+
        "the statue that seems to be lighting the room.\n");

    add_item(({"mysterious glow","glow"}),"The glow seems to be coming "+
        "from inside the middle of the statue, around the stomach region "+
        "you imagine.  There does not seem to be any fire, or obvious "+
        "light source to be giving off such a glow.  You conclude it "+
        "could only be magical in nature.\n");

    add_exit(CAVE+"water/room1","north");
}

void
init()
{
    ::init();
    add_action("try_place","place");
    add_action("try_place","hold");
}

int
try_place(string str)
{
    notify_fail("Place what?\n");
    if (str == "my hands above my head")
    {
    this_player()->catch_msg("You are sucked into the light inside "+
        "the statue.\n");
    this_player()->move_living("into the glow inside the statue",CAVE+"room33",1);
    return 1;
    }
    return 0;
}
