inherit "/std/room.c";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "../defs.h"

#define IFTP if (this_player()->query_skill (SS_AWARENESS) <= 10)

void
create_room()
{
    set_short("Warehouse");
    set_long(break_string(
"This is an old, abandoned warehouse on the north side of the city.  This " +
"place held items to be shipped out of town in the old days, but now it is " +
"almost completly empty, except for some large boxes in one dark corner.  " +
"Everything of value has been long since cleared out of " +
"here.\n", 78));

    add_exit(G_ROOMS + "outside", "west", "@@block");
    
    add_item(({"box", "boxes", "large boxes"}), "@@box_desc@@");
    
    add_item(({"crate", "large crate", "wooden crate"}), "@@crate_desc");

    add_item(({"nail", "nails"}), break_string(
"After further inspection, you notice a tiny bit of blood, and a whisper of "+
"black cloth on one of the nails towards the back.  Doesn't neccessarily " +
"mean anything, does it?  The nails protrude far into the crate.  Make " +
"sure you are careful if you go inside.\n", 78));

    add_prop(ROOM_I_INSIDE, 1);
}

int
block()
{
    write (
"Well, this warehouse has not been connected to the real world, yet.\n");
    return 1;
}

string
box_desc()
{
    IFTP return BS("Nothing but a bunch of broken wooden boxes. Not even " +
                "worth the trouble.\n"); 
    else return BS("Nothing but a bunch of broken wooden boxes and one " +
                "large wooden crate. Not even worth the trouble.\n");
}

string
crate_desc()
{
    IFTP return "What crate?\n";
    else return
"This crate is roughy man-sized, and is made of cheap pine wood.  It is\n" +
"falling apart but still intact, and there are many rusty nails sticking\n" +
"out of its surface.  It looks empty, but you wonder what it might have\n " +
"once contained.\n";
}


void
init()
{
    ::init();
    add_action("enter_crate", "enter");
}

int
enter_crate(string str)
{
    notify_fail("Enter what?\n");
    if (!str)
        return 0;
    if(str != "crate" && str != "large crate" && str != "wooden crate")
        return 0;
    IFTP
    {
        say (QCTNAME(this_player()) + "looks confused.\n");
    return 0;
    }
    this_player()->move_living(
        "into a dark corner of the room, and dissapears from view.", 
        G_ROOMS + "crate", 1);
    return 1;
}

