/* 
 *  This is the first floor in the tower of realms
 * 
 *  Coded by Maniac 20/12/96
 */ 

#include <stdproperties.h>
#include "tower_test.h"
#include "../defs.h"

inherit TOWER_FLOOR;

void
create_tower_floor()
{
    set_short("Tower of Realms Floor One"); 
    set_long("This is the first floor of the Tower of Realms. " + 
        FLOOR_MAINDESC + FLOOR_STAIRDESC + "\n"); 

    set_floor_number(1); 
    ADD_FLOOR_ITEMS

    add_prop(ROOM_S_MAP_FILE, "tower_map.txt");

    add_exit(TOWN_DIR + "tower", "down", 0); 
    add_exit(TOWN_DIR + "tfloor2", "up", 0); 
}