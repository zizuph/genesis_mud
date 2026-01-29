/*
 * Anorien - /d/Gondor/anorien/plains/an2w2n.c
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
    set_items_entwash();
    set_herbs_2();
    
    set_short("Anorien");
    set_long("The " + VBFC("daylight_desc") + " shines down upon " +
        "the tall green grass that surrounds you. Not far to the south, " +
        "a dusty stone road is barely visible before the fields climb up " +
        "to the snow-capped peaks of the White Mountains. Lush green " +
        "fields stretch out in all directions, while the bright " +
        VBFC("light_type") + " dances merrily along the surface of the " +
        "Entwash that flows just north of here. Several groves of trees " +
        "are scattered all around, dotting the plains in every direction.\n"); 

    add_trees(1);

    add_tell("A swirling wind follows the sparkling river through " +
        "the fields, causing the tall grasses to bend and sway.\n");
    add_tell("A large, silver fish jumps high out of the sparkling " +
        "waters of the Entwash, landing again with a loud splash.\n");
    add_tell("A large, brown fish jumps high out of the sparkling " +
        "waters of the Entwash, landing again with a loud splash.\n");
    add_tell("A small, silver fish jumps high out of the sparkling " +
        "waters of the Entwash, landing again with a loud splash.\n");
    
    set_no_exit_msg(({"north","northeast","northwest"}),
        "The ground seems to get wetter the further north you go, and " +
        "it quickly becomes apparent that you cannot make any further " +
        "progress in that direction.\n");

    add_exit(PLAINS_DIR + "an3w2n", "east",0,2,1);
    add_exit(PLAINS_DIR + "an1w2n", "west",0,2,1);
    add_exit(ROAD_DIR + "wr14","southwest",0,0,1);
    add_exit(ROAD_DIR + "wr13","south",0,0,1);
    add_exit(PLAINS_DIR + "an3w3n","southeast",0,2,1);

    set_drink_from(({"waters", "river", "entwash"}));
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
    write("With a little effort, you make your way to the banks of the " +
        "Entwash and take a long refreshing drink.\n");
    say(QCTNAME(TP) + " wanders north towards the Entwash to enjoy a cool " +
        "drink of water.\n");
}
/* drink_message */
