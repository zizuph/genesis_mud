/*
 * Thornhold
 * -- Tomas 2019
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include <filter_funs.h>
#include <macros.h>
#include <time.h>
#include <formulas.h>
#include <composite.h>
#include <cmdparse.h>
#include <tasks.h>


inherit BASE_ROAD;


#define ROOM ({ "/d/Faerun/thornhold/rooms/test.c" })


void
create_road()
{
    set_short("This is a test room. Careful not to trip over " +
    "all the bits and bytes littering the floor");
    reset_faerun_room();
}

public void
enter_inv(object ob, object from)
{
	string *names;
	::enter_inv(ob, from);
}

public void
init()
{
    ::init();
}

/*
int
do_sword_damage()
{
	object *inv, *live, room;
	int i;

	inv = ({ });
	for(i = 0; i < sizeof(ROOM); i++)
		if((room = find_object(ROOM[i])))
			inv += all_inventory(room);
	
	if(sizeof(inv))
	{
	//	live = FILTER_LIVE(inv);
		live = FILTER_LIVE(all_inventory(environment(live[0]))) -
            ({ live[0] });
		live = FILTER_CAN_SEE(live, TP);
		if(sizeof(live))
			tell_room(TO, "The dropped sword bounces off the ground, " +
			"slicing into you! OUCH!!\n");
			say(" drops the sword, which bounces into "+QTNAME(live[0])+  
			"!\n",live[0]);
			live[0]->add_hp(-(live[0]->query_max_hp()/10));
	}
	return 1;
}
*/

public void
resolve_damage(object *targets)
{
    int i;
    
	// Find everyone in our environment except the caster and the primary
	// target
	targets = FILTER_LIVE(all_inventory(environment(targets[0]))) - ({ targets[0] });

	// Loop through all the targets
	for(i=0;i<sizeof(targets);i++)
	{
		targets[i]->catch_msg("gets hit by the dropped sword.\n");
        tell_room(environment(targets[i]), QCTNAME(targets[i]) +
        	" gets hit by the sword.\n", targets[i]);
    }
}

