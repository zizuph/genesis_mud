/*
 * Balcony in the vampire manor
 * Louie 2006
 */
  
#pragma strict_types
#include "defs.h"

inherit VAMP_ROOM_DIR + "vamp_room";

#include <stdproperties.h>
#define FALL_ROOM (VAMP_ROOM_DIR+"manor/falling_room")

//proto
int do_leap(string str);

void
create_vamp_room()
{
    set_short("balcony");
    set_long("You stand on a balcony overhanging a sheer dropoff "+
        "to water far below.  "+
        "The wind blows coldly across the semi-circle of stone "+
        "which makes up the balcony ledge.  "  +
        "A low lip of stone is all that attempt to prevent "+
        "someone from leaping off the balcony to the water below.  "+
        "A narrow hallway leads south back into the manor.  "+
        "\n");

    add_exit("narrowhall.c", "south");

    add_item(({"south","hall","narrow hall","narrow hallway"}),
        "To the south is a narrow hallway leading into the manor.\n");
    
    add_item(({"water","below","down","cliff","dropoff",
        "sheer dropoff"}),
        "Peering over the edge of the balcony, you can see a sheer "+
        "dropoff along a cliff wall, ending in water far below.  "+
        "\n");

    add_item(({"ledge","lip","stone lip","low lip","low stone lip",
        "balcony ledge","balcony"}),
        "An edge of stone, roughly two feet high and a foot deep, "+
        "runs along the edge of the semi-circle of the balcony to "+
        "prevent someone from accidentally walking off.  "+
        "\n");

    
    //Add ability to leap off the balcony :P
}

void
init() {
    ::init();
    add_action(do_leap, "leap");
    add_action(do_leap, "jump");
    add_action(do_leap, "walk");
}

int do_leap(string str)
{
    if (!strlen(str)) {
        notify_fail("Leap off of the balcony?\n");
        return 0;
    }

    if (str != "off" 
        && str != "off balcony"
        && str != "off of balcony"
        && str != "off of the balcony"
        && str != "off ledge"
        && str != "off of ledge"
        && str != "off of the ledge"
        && str != "down"
        && str != "off cliff"
        && str != "edge"
        && str != "into water"
        && str != "water"
        && str != "dropoff")
    {
        notify_fail("Leap off of the balcony?\n");
        return 0;
    }

    object tp = this_player();

    tp->catch_msg("\nGoodbye cruel world!\n\n");
    say(QCTNAME(tp)+" leaps off of the balcony into the empty air!\n");

    tp->move_living("M",FALL_ROOM, 1, 0);

    return 1;

}
