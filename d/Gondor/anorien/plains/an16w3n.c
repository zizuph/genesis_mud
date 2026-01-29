/*
 * Anorien - /d/Gondor/anorien/plains/an16w3n.c
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
    set_herbs_8();
    
    set_short("In Anorien, along the Anduin near Cair Andros");
    set_long("You are wandering across the rolling plains of Anorien, near " +
        "a well travelled ford that leads across the Anduin River to the " +
        "island of Cair Andros to the east. Small groves of tall trees " +
        "follow the rushing waters of the river south, while the gentle " +
        VBFC("light_type") + " falls down upon fields of green grass and " +
        "bright wildflowers which extend into the distance to the west. " +
        "Far away to the south, the jagged snow-capped peaks of the White " +
        "Mountains march gracefully across the horizon.\n");

    add_trees(1);

        add_tell("A swirling wind follows the sparkling river through " +
            "the fields, causing the tall grasses to bend and sway.\n");
        add_tell("The dull roar of the river echoes across the land " +
            "as the rushing waters tumble past through the fields.\n");
        add_tell("A large, silver fish jumps high out of the sparkling " +
            "waters of the river, landing again with a loud splash.\n");
        add_tell("A large, brown fish jumps high out of the sparkling " +
            "waters of the river, landing again with a loud splash.\n");
        add_tell("A small, silver fish jumps high out of the sparkling " +
            "waters of the river, landing again with a loud splash.\n");
        add_tell("The surface of the Anduin River ripples slightly as the " +
            "waters run over the shallows of the ford.\n");
        add_tell("You hear a voice shout out from the fortress on the " +
            "island to the east.\n");

    set_no_exit_msg(({"northeast","southeast"}),
        "The rushing waters of the Anduin River are far too strong to " +
        "cross here. There appears to be a ford east of here, " +
        "connecting to the island in the middle of the river.\n");

    add_exit(PLAINS_DIR + "an15w4n","southwest",0,4,1);
    add_exit(PLAINS_DIR + "an16w4n","south",0,4,1);
    add_exit(PLAINS_DIR + "an15w3n","west",0,4,1);
    add_exit(PLAINS_DIR + "an15w2n","northwest",0,4,1);
    add_exit(PLAINS_DIR + "an16w2n","north",0,4,1);
    add_exit(CAIRANDROS_DIR + "w_ford","east","@@ford@@",5,1);

    add_npc(AN_NPC_DIR + "captain");
    add_npc(AN_NPC_DIR + "soldier", 3);

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

/*
 * Function name:        ford
 * Description  :        Provides a description for entering the ford
 */
int
ford()
{
    find_living("varian")->catch_tell("****  " +
        capitalize(this_player()->query_real_name()) + " is visiting " +
        "Cair Andros  ****----\n\n");
    write("You enter the ford and begin to wade across the Anduin.\n");
    say(QCTNAME(TP) + " wades east into the river.\n");
}