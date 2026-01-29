/*
 * Cair Andros - /d/Gondor/anorien/cairandros/caf7.c
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
    set_long("You are around the southeast corner of the stone fortress, " +
        "walking along a stone parapet that overlooks the island of " +
        "Cair Andros. You can see the " + VBFC("light_type") + " from the " + 
        VBFC("day_desc") + " " + VBFC("sun_moon") + " as it squeezes through " +
        "the crenellations, leaving the merlons to cast shadows across " +
        "the length of the stone floor. There is a stone pathway that " +
        "follows the parapet, eventually leading back to the stairs that " +
        "are north and east of here. Looking over the stone walls, you " +
        "can see the the winding silver ribbon of the Anduin river as " +
        "it cuts through the lands of Gondor.\n"); 

    add_item(({"stair","stairs","step","steps","stone stair","stone stairs",
            "staircase","stone staircase"}),
        "Although you cannot see them from here, the stairs you came " +
        "up are on the other end of this pathway, to the north and east.\n");
    add_item(({"path","pathway"}),
        "A wide path of stone follows the walls along the perimeter of " +
        "the fort, clearly giving the soldiers space to ogranize " +
        "themselves in the event of an enemy assault.\n");

    set_no_exit_msg(({"southwest","east", "northwest","south","southeast"}),
        "Jumping over the top of the wall would not be a good idea! " +
        "Perhaps you should look for another direction to go in.\n");
    set_no_exit_msg(({"northeast"}),
        "A sturdy wall prevents you from going further into the middle " +
        "of the fort.\n");

    add_exit(CAIRANDROS_DIR + "caf6", "east",0,0,0);
    add_exit(CAIRANDROS_DIR + "caf8", "north",0,0,0);

    add_npc(CA_NPC_DIR + "captain");
    add_npc(CA_NPC_DIR + "soldier", 2);
    add_npc(CA_NPC_DIR + "soldier2", 1);
}