/*
 * Anorien - /d/Gondor/anorien/plains/an16w4n.c
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
    set_items_cairandros();
    set_herbs_9();
    
    set_short("Anorien");
    set_long("You are passing through the rolling plains of Anorien, " +
        "with the " + VBFC("light_type") + " illuminating the rushing " +
        "waters of the Anduin River as they flow past Cair Andros to the " +
        "east. The fields around you are filled with a tall green grass, " +
        "while bright wildflowers add a splash of colour around the " +
        "groves of trees that have been sprinkled everywhere. Far to the " +
        "south, you can see the snow-capped peaks of the White Mountains " +
        "as they reach up into the " + VBFC("day_desc") + " sky.\n");

    add_trees(1);

    add_tell("A swirling wind follows the sparkling river through " +
        "the fields, causing the tall grasses to bend and sway.\n");
    add_tell("The dull roar of the Anduin echoes across the land " +
        "as the rushing waters tumble past through the fields.\n");
    add_tell("A large, silver fish jumps high out of the sparkling " +
        "waters of the Anduin, landing again with a loud splash.\n");
    add_tell("A large, brown fish jumps high out of the sparkling " +
        "waters of the Anduin, landing again with a loud splash.\n");
    add_tell("A small, silver fish jumps high out of the sparkling " +
        "waters of the Anduin, landing again with a loud splash.\n");

    set_no_exit_msg(({"northeast","east","southeast"}),
        "The rushing waters of the Anduin River are far too strong to " +
        "cross here. There appears to be a ford just north of here, " +
        "connecting to the island in the middle of the river.\n");

    add_exit(PLAINS_DIR + "an15w5n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an16w5n","south",0,2,1);
    add_exit(PLAINS_DIR + "an15w4n","west",0,2,1);
    add_exit(PLAINS_DIR + "an15w3n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an16w3n","north",0,2,1);

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
        "Anduin and take a long refreshing drink.\n");
    say(QCTNAME(TP) + " wanders east towards the Anduin to enjoy a cool " +
        "drink of water.\n");
}
/* drink_message */
