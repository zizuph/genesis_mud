/*
 * Cair Andros - /d/Gondor/anorien/cairandros/caf6.c
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
    set_long("You are near the southeast corner of the stone fortress, " +
        "walking along the parapet. The " + VBFC("light_type") + " from the " + 
        VBFC("day_desc") + " " + VBFC("sun_moon") + " peeks through " +
        "the crenellations, causing the merlons to cast shadows across " +
        "the stone floor. A stone pathway follows the parapet to both " +
        "the west and north where several stone stairs descend " +
        "into the heart of the fortress. Gazing out beyond the walls, " +
        "you can see the sparkling waters of the Anduin river as they " +
        "flow around the island, wandering southward towards the " +
        "sea.\n"); 

    add_item(({"stair","stairs","step","steps","stone stair","stone stairs",
            "staircase","stone staircase"}),
        "Just north of here, you can see some stone stairs leading down " +
        "into the fortress.\n");
    add_item(({"path","pathway"}),
        "A wide path of stone follows the walls along the perimeter of " +
        "the fort, clearly giving the soldiers space to ogranize " +
        "themselves in the event of an enemy assault.\n");

    set_no_exit_msg(({"southwest","east", "northeast","south","southeast"}),
        "Jumping over the top of the wall would not be a good idea! " +
        "Perhaps you should look for another direction to go in.\n");
    set_no_exit_msg(({"northwest"}),
        "A sturdy wall prevents you from going further into the middle " +
        "of the fort.\n");

    add_exit(CAIRANDROS_DIR + "caf5", "north",0,0,0);
    add_exit(CAIRANDROS_DIR + "caf7", "west",0,0,0);

    add_npc(CA_NPC_DIR + "captain");
    add_npc(CA_NPC_DIR + "soldier", 3);
}