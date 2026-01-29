/*
 * Anorien - /d/Gondor/anorien/plains/an14w2n.c
 *
 * Varian 2016
 */

#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit ANORIEN_STD_DIR + "base";

void 
create_plains_room()
{
    set_items_plains();
    set_items_anduin();
    set_herbs_6();
    
    set_short("Anorien");
    set_long("You are travelling along the banks of the Anduin, just " +
        "west of where the Entwash joins the river. Rolling hills " +
        "covered in a blanket of colourful wildflowers and tall " +
        "green grass cover the plains of Anorien, dotted with many " +
        "small tree groves that provide shelter across the land. The " +
        "Anduin continues to flow deeper into Gondor to the east, while " +
        "far in the distance to the south, the jagged peaks of the " +
        "White Mountains look up at the " + VBFC("day_time") + " " +
        VBFC("sun_moon") + " above.\n");

    add_trees(1);
    
    add_tell("The dull roar of the Anduin echoes across the land " +
        "as the rushing waters tumble past through the fields.\n");
    add_tell("A large, silver fish jumps high out of the sparkling " +
        "waters of the Anduin, landing again with a loud splash.\n");
    add_tell("A large, brown fish jumps high out of the sparkling " +
        "waters of the Anduin, landing again with a loud splash.\n");
    add_tell("A small, silver fish jumps high out of the sparkling " +
        "waters of the Anduin, landing again with a loud splash.\n");

    set_no_exit_msg(({"north","northeast"}),
        "The mouths of the entwash have flooded the land in that " +
        "direction, you will have to find another way around.\n");


    add_exit(PLAINS_DIR + "an13w3n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an14w3n","south",0,2,1);
    add_exit(PLAINS_DIR + "an15w3n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an13w2n","west",0,2,1);
    add_exit(PLAINS_DIR + "an15w2n","east",0,2,1);
    add_exit(PLAINS_DIR + "an13w1n","northwest",0,2,1);

    set_drink_from(({"waters", "river", "anduin"}));
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
        "Anduinand take a long refreshing drink.\n");
    say(QCTNAME(TP) + " wanders north towards the Anduin to enjoy a cool " +
        "drink of water.\n");
}
/* drink_message */