/*
 * Anorien - /d/Gondor/anorien/plains/an1w2n.c
 *
 * Varian 2016
 */

#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit ANORIEN_STD_DIR + "base";

public void drink_message(string from);

/*
 * Function name:        create_plains_room()
 * Description  :        Creates the plains from from the base file
 *                       /d/Gondor/anorien/std/base.c
 */
void 
create_plains_room()
{
    set_items_plains();
    set_items_road();
    set_items_stream();
    set_items_entwash();
    set_herbs_1();
    
    set_short("Anorien");
    set_long("You are in the green, grassy fields of Anorien where " +
        "the " + VBFC("light_type") + " from the " + VBFC("day_desc") + 
        " " + VBFC("sun_moon") + " illuminates the fields around you. To " +
        "the south, the " + VBFC("daylight_desc") + " reveals the " +
        "outline of a dusty stone road running from east to west through " +
        "the ancient trees of the Firien Wood, while the " + 
        "snow-capped peaks of the White Mountains stand tall in the " +
        "distance. To the west, the Mering Stream runs north to join " +
        "the marshy lands surrounding the Entwash which runs nearby, " +
        "while to the east wide grassy plains dotted with groves of trees " +
        "spread out all the way to the Anduin.\n"); 

    add_trees(1);

    add_tell("A swirling wind follows the sparkling river through " +
        "the fields, causing the tall grasses to bend and sway.\n");
    add_tell("A large, silver fish jumps high out of the sparkling " +
        "waters of the Entwash, landing again with a loud splash.\n");
    add_tell("A large, brown fish jumps high out of the sparkling " +
        "waters of the Entwash, landing again with a loud splash.\n");
    add_tell("A small, silver fish jumps high out of the sparkling " +
        "waters of the Entwash, landing again with a loud splash.\n");

    set_no_exit_msg(({"southwest","west", "northwest"}),
        "The swift waters of the Mering Stream, the traditional border " +
        "between Gondor and Rohan, prevents you from going in that " +
        "direction. You will need to go south to the road in order " +
        "to cross into Rohan.\n");
    set_no_exit_msg(({"north","northeast"}),
        "The ground seems to get wetter the further north you go, and " +
        "it quickly becomes apparent that you cannot make any further " +
        "progress in that direction.\n");

    add_exit(PLAINS_DIR + "an2w2n", "east",0,2,1);
    add_exit(ROAD_DIR + "wr14","south",0,0,1);
    add_exit(ROAD_DIR + "wr13","southeast",0,0,1);

    set_drink_from(({"stream", "river", "mering stream"}));
}
/*
 * Function name:        init
 * Description  :        Initializes commands for players
 */
void
init()
{
    ::init();
    init_drink();
}
/*
 * Function name:        drink_message
 * Description  :        Provides a description for drinking from the river
 */
public void
drink_message(string from)
{
    write("You kneel down beside the Mering Stream and cupping your hands, " +
        "enjoy a nice drink of clean cool water.\n");
    say(QCTNAME(TP) + " bends down to drink some water from the Mering " +
        "stream.\n");
}
/* drink_message */