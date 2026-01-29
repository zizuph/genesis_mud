// /d/Genesis/start/human/town/tfloor5.c

/* 
 *  This is the fifth floor in the tower of realms
 * 
 *  Added by Styles 07/03/2008 since his original domain office
 *  was occupied by someone else...
 *
 *  Edit 210729:
 *  This is no longer the link to the Liwitch domain office.
 *  Actually, this file is obsolete and should not be used until
 *  a new floor is added to the tower. If that is done then do
 *  remember to move the code leading to the attic in the file 
 *  that is the top floor.  /Styles.
 *  
 */ 

#include <stdproperties.h>
#include "tower.h"
#include "../defs.h"

inherit TOWER_FLOOR;

void
create_tower_floor()
{
     set_short("Tower of Realms Floor Five"); 
     set_long("This is the fifth floor of the Tower of Realms. " +
              FLOOR_MAINDESC + "\n");
     set_floor_number(5); 
     ADD_FLOOR_ITEMS;

    add_prop(ROOM_S_MAP_FILE, "tower_map.txt");

  // add_exit("/d/Liwitch/common/player_domain_office", "east", 0); 
     add_exit(TOWN_DIR + "tfloor4", "down", 0); 
  // add_exit(TOWN_DIR + "tfloor6", "up", 0); 
}

