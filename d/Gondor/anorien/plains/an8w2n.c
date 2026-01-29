/*
 * Anorien - /d/Gondor/anorien/plains/an8w2n.c
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
    set_herbs_8();
    
    set_short("Anorien");
    set_long("You are wandering in the tall green grass that covers the " +
        "plains of Anorien, illuminated by the light of the " + 
        VBFC("sun_moon") + " above. The fields are covered in colourful " +
        "patches of wildflowers sprinkled around the dozens of tree " +
        "groves that stretch out in every direction. To the north, the " +
        "mouths of the Entwash empty into the rushing waters of the " +
        "mighty Anduin River that borders the fields to the east. Far " +
        "to the south, the " + VBFC("light_type") + " falls upon the " +
        "White Mountains as their jagged peaks scrape at the " +
        VBFC("day_desc") + " sky above.\n");

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

    add_exit(PLAINS_DIR + "an9w2n", "east",0,2,1);
    add_exit(PLAINS_DIR + "an7w2n", "west",0,2,1);
    add_exit(PLAINS_DIR + "an7w3n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an8w3n","south",0,2,1);
    add_exit(PLAINS_DIR + "an9w3n","southeast",0,2,1);
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
