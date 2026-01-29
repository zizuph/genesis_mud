/* created by Aridor 01/05/94 */

#include "../local.h"
#include <ss_types.h>
#include <filter_funs.h>
#define WATER_OUTLET    ROOM + "secret3"

inherit INSIDE_BASE;

int trigger_active = 0;

void
create_splains_room()
{
    set_short("In a duct");
    set_long("You are in a duct, there is a shimmer of light to your west " +
	     "and it is completely dark down from here.\n");
    DARK;
    add_exit(ROOM + "secret2","down");
    add_exit(ROOM + "under_bridge","west");
}

void
init()
{
    if (trigger_active)
      set_alarm(1.0,0.0,"rush_water_through");
    ::init();
}

void
rush_water_through()
{
    int i;
    object *whos;
    if (trigger_active)
      trigger_active = 0;
    else
      return;
    tell_room(TO, ({"Suddenly, something opens in the north wall and a gush " +
		    "of water floods the room!\n","Suddenly, something " +
		    "opens in the north wall and a gush of water floods the " +
		    "room!\n","Suddenly, you can hear water rushing towards " +
		    "you.\n"}));
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
