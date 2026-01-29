/* 	
 * pond.c			Styles.   3 Mar 1993
 *
 *  Modified - Varian  March, 2016
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/start/human/wild2/base";

public void drink_message(string from);

void
create_wild_room()
{
    set_items_sparkle();
    set_items_driver();
    set_items_field();
    set_herbs();

    set_short("By the pond");
    set_long("You are walking along a small trail that follows the northern " +
        "bank of the Diamond River as it wanders east towards the Pen Sea. " +
        "A small pond has pooled here, filled with rushes and reeds, " +
        "seemingly just waiting for some ducks to come and swim in it. " +
        "The land all around you is filled with wide fields of tall " +
        "yellow and green grass, haphazardly decorated with splashes of " +
        "colour from dozens of beautiful wildflowers which grow around the " +
        "small groves of trees that dot the plains. The jagged peaks " +
        "of the Grey Mountains rise up high above you to the north " +
        "and west, framing the perimeter of Sparkle valley. To the " +
        "east, you can see a tumbled heap of stone jutting out of " +
        "the fields, appearing to be the ruined remnants of some ancient " +
        "building. The trail you are walking on connects back to the " +
        "Dark Road to the north and continues to follow the river " +
        "to the southeast.\n");

    add_trees(0);

    add_exit(THIS_DIR + "field9","north");
    add_exit(THIS_DIR + "field10","northeast",0,1,1);
    add_exit(THIS_DIR + "wfall","northwest",0,1,1);
    add_exit(THIS_DIR + "ruin","east",0,1,1);
    add_exit(THIS_DIR + "pond", "west", "@@riv@@", 1,1);
    add_exit(THIS_DIR + "pond", "southwest", "@@riv@@", 1,1);
    add_exit(THIS_DIR + "pond", "south", "@@riv@@", 1,1);
    add_exit(THIS_DIR + "field6", "southeast");

    add_item(({"pond","small pond","pool","small pool"}),
        "This small pond has pooled near the banks of the small stream " +
        "nearby.\n");
    add_item(({"rushes","rush","reed","reeds"}),
        "Standing tall in the pond, several clumps of rushes and " +
        "reeds would provide a perfect home for any stray ducks.\n");
    add_item(({"duck","ducks"}),
        "How strange, there are no ducks in this pond! This looks like " +
        "a perfect home for some ducks, but you cannot see a single duck " +
        "anywhere.\n");
    add_item(({"river","diamond river","steam","large stream"}),
        "This stream actually appears to be the Diamond River. The river " +
        "slowly grows in size and strength the further east it flows.\n");
    add_item(({"tributaries","streams","tributary","tiny stream",
            "tiny streams"}),
        "There are several tiny streams which wind across the fields, " +
        "tributaries of the larger Diamond River which flows east " +
        "towards the Pen Sea.\n");
    add_item(({"heap","tumbled heap","ruin","ruins","building",
                "ancient building"}),
        "It is hard to say for sure, but it seems like this mound is the " +
        "ruins of some ancient building. Although, who would build " +
        "something out in the middle of these plains is a mystery to you.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");

    set_drink_from(({"stream", "river", "diamond river", "pond", "pool"}));
    
}

void

init()
{
    ::init();
    init_drink();
}

/*
 * Function name:        drink_message
 * Description  :        Provides a description of drinking from the river
 */
public void
drink_message(string from)
{
    write("Wandering over to the pond where it bends to meets the river, " +
        "you stoop down and cup your hands to take a drink of fresh " +
        "water.\n");
    say(QCTNAME(TP) + " bends down to drink some fresh water.\n");
}
/* drink_message */

/*
 * Function name:        riv
 * Description  :        Provides an explanation why a mortal cannot move
 *                       across the river in that direction
 * Returns      :        int 1 - Prevents mortal from moving through the exit
 */
int
riv()
{
    write("The stream here is too wide to cross, you will have to find a " +
        "bridge or something.\n");
    return 1;
}
/* riv */