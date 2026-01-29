/*
 * Anorien - /d/Gondor/anorien/plains/an16w11n.c
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
    set_items_road();
    set_items_city();
    set_herbs_7();
    
    set_short("Anorien");
    set_long("You are standing beside the ruins of Osgiliath, near the " +
        "banks of the Anduin River that rushes past to the east. A " +
        "dusty stone road passes in front of Rammas Echor, the massive " +
        "stone wall that surrounds the citadel of Minas Tirith which " +
        "sits upon the eastern edge of the White Mountains to the west. " +
        "The rolling plains of Anorien stretch out to the north, under the " +
        VBFC("day_time") + " sky, with dozens of groves of trees sprinkled " +
        "across the fields of wildflowers and tall green grass which " +
        "surround you.\n");

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

    set_no_exit_msg(({"northeast","east"}),
        "The rushing waters of the Anduin River are far too strong to " +
        "cross here. There appears to be a ford north of here, " +
        "connecting to the island in the middle of the river.\n");
    set_no_exit_msg(({"southeast","south"}),
        "The ruined city of Osgiliath lies directly in your path, " +
        "you will need to follow the road that passes just southwest of " +
        "you here to get inside.\n");

    add_exit(ROAD_DIR + "or2","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w11n","west",0,2,1);
    add_exit(PLAINS_DIR + "an15w10n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an16w10n","north",0,2,1);

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
