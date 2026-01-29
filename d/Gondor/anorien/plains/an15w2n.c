/*
 * Anorien - /d/Gondor/anorien/plains/an15w2n.c
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
    set_herbs_7();
    
    set_short("Anorien");
    set_long("You are travelling across the rolling plains of Anorien, " +
        "through the tall green grass that sways gently in the breeze. " +
        "The endless roar of the Anduin River echoes as it swirls " +
        "past, framed by the countless wildflowers and groves of " +
        "trees that grow along the banks. Far away, across the southern " +
        "horizon, the rocky peaks of the White Mountains stand stoically " +
        "beneath the " + VBFC("sun_moon") + " in the " + VBFC("day_desc") + 
        " sky above.\n");

    add_trees(1);

    add_tell("The dull roar of the Anduin echoes across the land " +
        "as the rushing waters tumble past through the fields.\n");
    add_tell("A large, silver fish jumps high out of the sparkling " +
        "waters of the Anduin, landing again with a loud splash.\n");
    add_tell("A large, brown fish jumps high out of the sparkling " +
        "waters of the Anduin, landing again with a loud splash.\n");
    add_tell("A small, silver fish jumps high out of the sparkling " +
        "waters of the Anduin, landing again with a loud splash.\n");
    add_tell("A swirling wind follows the sparkling river through " +
        "the fields, causing the tall grasses to bend and sway.\n");
    
    set_no_exit_msg(({"northwest","north","northeast"}),
        "The mouths of the anduin have flooded the land in that " +
        "direction, you will have to find another way around.\n");

    add_exit(PLAINS_DIR + "an14w3n","southwest",0,2,1);
    add_exit(PLAINS_DIR + "an15w3n","south",0,2,1);
    add_exit(PLAINS_DIR + "an16w3n","southeast",0,2,1);
    add_exit(PLAINS_DIR + "an14w2n","west",0,2,1);
    add_exit(PLAINS_DIR + "an16w2n","east",0,2,1);

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
        "Anduih and take a long refreshing drink.\n");
    say(QCTNAME(TP) + " wanders north towards the Anduin to enjoy a cool " +
        "drink of water.\n");
}
/* drink_message */