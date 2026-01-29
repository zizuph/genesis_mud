/*
 * Anorien - /d/Gondor/anorien/plains/an16w10n.c
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
    set_items_city();
    set_herbs_6();
    
    set_short("Anorien");
    set_long("You are travelling across the rolling plains of Anorien, " +
        "watching the " + VBFC("light_type") + " play on the surface " +
        "of the Anduin River as you stand on the western bank. The " +
        "forests of Ithilien grow on the eastern bank, following the " +
        "river all the way south to the nearby ruins of Osgiliath. " +
        "Colourful wildflowers grow amidst the tall green grass which " +
        "bends and sways in the wind, while groves of tall trees " +
        "are scattered all across the fields. Far to the south and " +
        "west, the city of Minas Tirith is visible, standing on " +
        "the eastern edge of the White Mountains that stretch across " +
        "the horizon.\n");

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
        "cross here. There appears to be a ford north of here, " +
        "connecting to the island in the middle of the river.\n");

    add_exit(PLAINS_DIR + "an15w11n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an16w11n","south",0,2,1);
    add_exit(PLAINS_DIR + "an15w10n","west",0,2,1);
    add_exit(PLAINS_DIR + "an15w9n","northwest",0,2,1);
    add_exit(PLAINS_DIR + "an16w9n","north",0,2,1);

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
