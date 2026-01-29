/* created by Aridor 01/05/94 */

#include "../local.h"
#include <ss_types.h>
#include <filter_funs.h>
#define WATER_OUTLET    ROOM + "secret4"

inherit INSIDE_BASE;

void
create_splains_room()
{
    set_short("In a duct");
    set_long("You are in a duct, going north and south. " +
	     "It is completely dark in either direction.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    DARK;
    add_exit(WATER_OUTLET,"north");
    add_exit(ROOM + "secret2","south");
}

void
rush_water_through()
{
    int i;
    object *whos;
    tell_room(TO, "Suddenly, you hear a load rushing noise coming from the " +
	      "south.\nSuddenly, a gush of water floods the room!\n");
    whos = FILTER_LIVE(all_inventory(TO));
    for(i=0;i<sizeof(whos);i++)
      if (random(whos[i]->query_stat(SS_STR)) <= random(200))
	{
	    whos[i]->catch_msg("The water carries you away!\n");
	    whos[i]->move_living("north, carried by the flood",
				 WATER_OUTLET,1,0);
	}
    whos = FILTER_DEAD(all_inventory(TO));
    for(i=0;i<sizeof(whos);i++)
      whos[i]->move(WATER_OUTLET);
    set_alarm(1.0,0.0,"flood_next_room");
}

void
flood_next_room()
{
    (WATER_OUTLET)->rush_water_through();
}
