/*
 * Anorien - /d/Gondor/anorien/plains/an13w2n.c
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
    set_items_anduin();
    set_herbs_5();
    
    set_short("Anorien");
    set_long("You are passing through the lands of Anorien, where the " +
        "mouths of the Entwash empty their grey waters into the Anduin. The " +
        "land itself is filled with rolling hills and plentiful tree " +
        "groves, all covered in a blanket of colourful wildflowers and a " +
        "tall green grass that blows back and forth in the wind. To the " +
        "east, the " + VBFC("daylight_desc") + " sparkles along the " +
        "surface of the Anduin river as it flows towards the sea. Far " +
        "away across the southern horizon, you can see the snow-capped " +
        "peaks of the White Mountains reaching up towards the " +
        VBFC("sun_moon") + " in the sky above.\n");

    add_trees(1);

    add_tell("A swirling wind follows the sparkling river through " +
        "the fields, causing the tall grasses to bend and sway.\n");
    add_tell("A large, silver fish jumps high out of the sparkling " +
        "waters of the Entwash, landing again with a loud splash.\n");
    add_tell("A large, brown fish jumps high out of the sparkling " +
        "waters of the Entwash, landing again with a loud splash.\n");
    add_tell("A small, silver fish jumps high out of the sparkling " +
        "waters of the Entwash, landing again with a loud splash.\n");
    add_tell("The dull roar of the Anduin echoes across the land " +
        "as the rushing waters tumble past through the fields.\n");
    add_tell("A large, silver fish jumps high out of the sparkling " +
        "waters of the Anduin, landing again with a loud splash.\n");
    add_tell("A large, brown fish jumps high out of the sparkling " +
        "waters of the Anduin, landing again with a loud splash.\n");
    add_tell("A small, silver fish jumps high out of the sparkling " +
        "waters of the Anduin, landing again with a loud splash.\n");

    set_no_exit_msg(({"northwest","northeast"}),
        "The mouths of the entwash have flooded the land in that " +
        "direction, you will have to find another way around.\n");

    add_exit(PLAINS_DIR + "an12w3n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an13w3n","south",0,2,1);
    add_exit(PLAINS_DIR + "an14w3n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an12w2n","west",0,2,1);
    add_exit(PLAINS_DIR + "an13w1n","north",0,2,1);
    add_exit(PLAINS_DIR + "an14w2n","east",0,2,1);

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
