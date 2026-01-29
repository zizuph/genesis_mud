/*
 * Dol Guldur - /d/Gondor/rhovanion/dolguldur/lane1.c
 *
 * Varian - November 2020
 */

#pragma strict_types

#include "/d/Gondor/rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit RHOVANION_DIR + "dolguldur/std/base";

/*
 * Function name:        create_dg_room()
 * Description  :        Creates the dg from from the base file
 *                       /d/Gondor/rhovanion/dolguldur/std/base.c
 */
void 
create_dg_room()
{

    set_items_city();
    
    set_short("Dol Guldur");
    set_long("You are currently following a small lane which hugs the " +
        "southern wall in the restored quarter of Dol Guldur. Huddled " +
        "together north of the lane are dozens, if not hundreds, of small " +
        "huts and shacks. Far distant to the north, in the middle of the " +
        "city and standing out in the " + VBFC("daylight_desc") + ", is " +
        "a jagged and broken tower. This small lane continues to wander " +
        "off to the east and back to the city gates just west of here.\n");

    add_item( ({"house", "houses", "hut", "huts", "shack", "shacks",
            "home", "homes", "small hut", "small huts", "small shack",
            "small shacks", "small homes", "small home", "small house",
            "small houses", "shelter"}),
        "There are dozens, perhaps hundreds, of small huts and shacks " +
        "piled up against each other on the north side of the lane.\n");
    add_item( ({"gate", "city gate", "gates", "city gates"}),
        "The gates of Dol Guldur are just west of you here.\n");
    add_item( ({"street", "wall street"}),
        "This lane follows the wall east of the gates in the restored " +
        "parts of Dol Guldur.\n");
    add_item( ({"wall", "city wall", "walls", "city walls"}),
        "The city walls of Dol Guldur rise up immediately before you as " +
        "this lane travels along them.\n");

    set_no_exit_msg( ({"northwest", "north", "northeast"}),
        "You attempt to enter one of the homes here but the door is " +
        "locked. On the other side, you hear someone shout 'Smeg off!'.\n");
    set_no_exit_msg( ({"southwest", "south", "southeast"}),
        "Yup, the city wall is definately restored! You will have to " +
        "go through the city gate if you want to get to the other side " +
        "of the wall.\n");

    add_exit(DG_DIR + "lane2", "east", 0, 3, 0);
    add_exit(DG_DIR + "entrance", "west", 0, 3, 0);
}