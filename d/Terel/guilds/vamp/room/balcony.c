/*
 * Balcony in the vampire manor
 * Louie 2006
 *
 * Modified: Novo 2008
 *
 */
  
#pragma strict_types
#include "defs.h"

inherit ROOM_DIR + "vamp_room";

#include <stdproperties.h>
#define FALL_ROOM (ROOM_DIR+"falling_room")

//proto
int do_leap(string str);

void
create_vamp_room()
{
    set_short("balcony");
    set_long("Here the stone of the manor and the stone of the hill "+
        "into which it is built meet and end in a sheer dropoff "+
        "overlooking a large body of water.  "+
        "A cold wind blows across the simple semi-circular balcony "+
        "which juts out over the ledge of the cliff.  "+
        "The lip of the balcony is rather low and just a hand-span "+
        "in width, hardly barrier enough to deter someone from "+
        "falling or leaping over its edge into the watery "+
        "depths far below.  "+
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
        "A rounded lip of stone, roughly knee-high and a hand-span, "+
        "deep, runs along the edge of the semi-circular balcony to "+
        "prevent someone from accidentally walking off.  "+
        "\n");

    remove_prop(ROOM_I_INSIDE);    
    add_prop(ROOM_I_LIGHT,1);
    
}

void
init() {
    ::init();
    add_action(do_leap, "leap");
    add_action(do_leap, "jump");
    add_action(do_leap, "walk");
    add_action(do_leap, "fall");

}

int do_leap(string str)
{
    if (!strlen(str)) {
        notify_fail("Be careful! You don't want to "+ query_verb() +
            " off of the balcony, do you?\n");
        return 0;
    }

    notify_fail("Be careful! You don't want to "+ query_verb() +
        " off of the balcony, do you?\n");
    if (!parse_command(str, ({ }),
        "'off' / 'into' / 'over' [of] [the] 'balcony' / 'cliff' / 'ledge' / 'water'"))
        return 0;    

    object tp = this_player();

    tp->catch_msg("\nGoodbye cruel world!\n\n");
    say(QCTNAME(tp)+" leaps off of the balcony and into the empty air!\n");

    tp->move_living("M",FALL_ROOM, 1, 0);

    return 1;

}
