/* created by Aridor 01/05/94 */

#include "../local.h"
#include <ss_types.h>
#include <filter_funs.h>
#define WATER_OUTLET    ROOM + "in_water6"

inherit INSIDE_BASE;

void
create_splains_room()
{
    set_short("In a duct");
    set_long("You are in a duct, it is coming from above you " +
	     "and from your south and leads north. A ladder leads up.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    DARK;
    add_exit(ROOM + "secret3","south");
    add_exit(WATER_OUTLET,"north","@@wash_away");
    add_exit(ROOM + "secret5","up");
}

int
wash_away()
{
    write("You take a step forward and plunge into water. The water rushes " +
	  "only a very short distance along the duct and you are swept out " +
	  "into the open.\n");
    return 0;
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
}
