/*
 * Anorien - /d/Gondor/anorien/plains/an6w2n.c
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
    set_items_entwash();
    set_herbs_6();
    
    set_short("Anorien");
    set_long("It is " + VBFC("day_desc") + " here in the northern parts " +
        "of Anorien. Wide fields of tall grass surround you in every " +
        "direction, bordered by the marshy lands near the mouths " +
        "of the Entwash to the north, and the jagged peaks of the " +
        "White Mountains that bask in the " + VBFC("daylight_desc") + 
        " across the southern horizon. Far to the east, the deep valley " +
        "which follows the mighty Anduin River is barely visible. Dozens " +
        "of groves of trees dot the plains here, filling the hills and " +
        "valleys with all manner of wildlife.\n");

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

    add_exit(PLAINS_DIR + "an7w2n", "east",0,2,1);
    add_exit(PLAINS_DIR + "an5w2n", "west",0,2,1);
    add_exit(PLAINS_DIR + "an5w3n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an6w3n","south",0,2,1);
    add_exit(PLAINS_DIR + "an7w3n","southeast",0,2,1);
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
