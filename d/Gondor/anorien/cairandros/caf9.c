/*
 * Cair Andros - /d/Gondor/anorien/cairandros/caf9.c
 *
 * Varian 2016
 */

#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit ANORIEN_STD_DIR + "ca_base";

/*
 * Function name:        create_ca_room()
 * Description  :        Creates the plains from from the base file
 *                       /d/Gondor/anorien/std/ca_base.c
 */
void 
create_ca_room()
{
    set_items_fort();
    set_items_river();
    
    set_short("On top of the fort at Cair Andros");
    set_long("You are wandering along the top of a tall fort on the " +
        "island of Cair Andros, overlooking the fords that cross the " +
        "Anduin River here. The " + VBFC("light_type") + " from the " + 
        VBFC("day_desc") + " " + VBFC("sun_moon") + " peeks through " +
        "the crenellations, as the merlons atop the rampart cast their " +
        "shadows. Every part of the fort appears to be made from " +
        "massive stone blocks, expertly cut and placed in such a " +
        "fashion as to make the fort appear quite formidable indeed. " +
        "A pathway follows the parapet to both the north and the " +
        "east, while a nearby set of sturdy stone stairs marches down into " +
        "the interior of the fort.\n"); 

    add_item(({"stair","stairs","step","steps","stone stair","stone stairs",
            "staircase","stone staircase"}),
        "These sturdy stone stairs provides access to the interior of " +
        "the fort below.\n");
    add_item(({"path","pathway"}),
        "A wide path of stone follows the walls along the perimeter of " +
        "the fort, clearly giving the soldiers space to ogranize " +
        "themselves in the event of an enemy assault.\n");

    set_no_exit_msg(({"southeast","east", "northwest","north","southwest"}),
        "Jumping over the top of the wall would not be a good idea! " +
        "Perhaps you should look for another direction to go in.\n");
    set_no_exit_msg(({"northeast"}),
        "A sturdy wall prevents you from going further into the middle " +
        "of the fort.\n");

    add_exit(CAIRANDROS_DIR + "caf12", "north",0,0,0);
    add_exit(CAIRANDROS_DIR + "caf10", "east",0,0,0);
    add_exit(CAIRANDROS_DIR + "fort8", "down",0,0,0);

    add_npc(CA_NPC_DIR + "captain");
    add_npc(CA_NPC_DIR + "soldier", 3);
}