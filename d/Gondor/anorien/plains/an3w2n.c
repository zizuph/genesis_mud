/*
 * Anorien - /d/Gondor/anorien/plains/an3w2n.c
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
    set_herbs_3();
    
    set_short("Anorien");
    set_long("It is " + VBFC("day_time") + " in the green fields of " +
        "Anorien, and the " + VBFC("light_type") + " shines across the " +
        "rolling hills which surround you. Dotted across the plains " +
        "are several groves of trees hidden amongst the tall green " +
        "grasses which sway gently in the breeze. Looking far to the south, " +
        "you watch the White Mountains march across the horizon, " +
        "overlooking a dusty stone road that you can see in the distance to " +
        "the southwest. To the north, the sluggish waters of the Entwash " +
        "slowly cut through marshy wetlands on its journey east to meet " +
        "up with the mighty Anduin River.\n");

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

    add_exit(PLAINS_DIR + "an4w2n", "east",0,2,1);
    add_exit(PLAINS_DIR + "an2w2n", "west",0,2,1);
    add_exit(ROAD_DIR + "wr13","southwest",0,0,1);
    add_exit(PLAINS_DIR + "an3w3n","south",0,2,1);
    add_exit(PLAINS_DIR + "an4w3n","southeast",0,2,1);
    set_drink_from(({"waters", "river", "entwash"}));

    add_prop(ROOM_S_MAP_FILE, "minas_tirith_road.txt");
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
