/*
 * Anorien - /d/Gondor/anorien/plains/an16w2n.c
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
    set_herbs_7();
    
    set_short("Anorien");
    set_long("You are standing on the banks of the Anduin river, near a " +
        "the heavily forested island of Cair Andros. The " + VBFC("light_type")
        + " dances brightly on the surface of the river, while also " +
        "illuminating the rolling plains that extend to the west. The " +
        "land is covered in a blanket of wildflowers and tall green grass, " +
        "with small groves of tall trees sprouting out quite frequently. " +
        "Far away to the south, you can see the rugged peaks of the " +
        "White Mountains as they march across the southern horizon.\n");

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

    set_no_exit_msg(({"northeast","east","southeast","north","northwest"}),
        "The rushing waters of the Anduin River are far too strong to " +
        "cross here. There appears to be a ford just south of here, " +
        "connecting to the island in the middle of the river.\n");

    add_exit(PLAINS_DIR + "an15w3n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an16w3n","south",0,2,1);
    add_exit(PLAINS_DIR + "an15w2n","west",0,2,1);

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
    say(QCTNAME(TP) + " wanders towards the Anduin to enjoy a cool " +
        "drink of water.\n");
}
/* drink_message */
