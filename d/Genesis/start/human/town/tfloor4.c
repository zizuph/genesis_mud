// /d/Genesis/start/human/town/tfloor4.c

/* 
 *  This is the fourth floor in the tower of realms
 * 
 *  Coded by Maniac 20/12/96
 *  Modded by Styles 2020-09-09
 *
 *
 *  A new version of this floor will come soon when 
 *  I'm done with my new domain office in the attic.
 *    /Styles.
 */ 



#include <stdproperties.h>
#include "tower.h"
#include "../defs.h"

inherit TOWER_FLOOR;

void
create_tower_floor()
{
     set_short("Tower of Realms Floor Four"); 
     set_long("This is the fourth floor of the Tower of Realms. " +
              "The floor and walls are made of polished marble, " +
              "reflecting your image as you look around in wonder. " +
              "From each floor it is possible to access the information " +
              "office of one or more domains. " +
           // "Broad stairs lead up to the next floor of the tower. " +
              "\n");

     set_floor_number(4); 
     ADD_FLOOR_ITEMS;

    add_prop(ROOM_S_MAP_FILE, "tower_map.txt");

     add_exit(TOWN_DIR + "tfloor3", "down", 0);

	 /* Removed whilst work is beeing done on the tower attic.
	  * Ref: /d/Liwitch/common/player_domain_office.c
	  * /Styles 2020-09-08.
      * 
	  * add_exit(TOWN_DIR + "tfloor5", "up", 0);
	 */

}

