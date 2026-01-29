/* Corridor-second floor 
 * Coded by Marisol (11/23/98)
 * Marisol Ramos (c) 1998
 */

#pragma strict_types

#include "../defs.h"

inherit CASTLE_OV2;

void
create_castle_room()
{
    set_em_long("This corridor enters to the human servant living "+
        "quarters. In this section, there are two doors on both side of "+
        "the corridor. The corridor end here. Human voices can be heard "+
        "behind the doors.\n");

    add_item("floor",                         
        "The floor here is made polished wooden boards that shines "+
        "a rich amber color.\n");

    add_exit("castle2_13", "west");
    add_door_exit(CASTLE_OBJ_DIR + "cdoor2_06", "castle2_10", "south");
    add_door_exit(CASTLE_OBJ_DIR + "cdoor2_06", "castle2_12", "north");
}                           
