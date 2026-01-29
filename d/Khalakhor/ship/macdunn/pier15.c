/* File:          /d/Khalakhor/ship/macdunn/pier15.c
 * Creator:       Damaris
 * Date:          03/2001
 * Modifications:
 * Purpose:       This is one of the piers.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/open/SHIPLINES
 *                /d/Khalakhor/ship/macdunn/std/pier_base.c
 *                /d/Khalakhor/ship/macdunn/crate.c
 * Comments:
 */

#pragma save_binary
#pragma strict_types


inherit "/d/Khalakhor/ship/macdunn/std/pier_base";
#include "local.h"
#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h"
object *workers;
public int *
query_local_coords()
{
	return ({9, 17});
}
public int
block_exit()
{
	write("The dock is under construction at the time.\n");
	return 1;
}
public void
reset_room()
{
	int i;
	
	if (!workers)
	workers = allocate(3);
	
	for (i = 0; i < sizeof(workers); i++)
	{
		if (!objectp(workers[i]))
		{
			workers[i] = clone_object("/d/Khalakhor/sw_speir/samorgan/npc/worker");
			
			if (i == 0)
			{
				workers[i]->set_team_leader();
			}
			else
			workers[i]->set_team_follower();
			workers[i]->set_team_name("fahlmar_guard_team");
			workers[i]->set_autoassist();
			workers[i]->arm_me();
			workers[i]->move(TO);
			tell_room(this_object(),
			capitalize(workers[i]->short()) + " arrives.\n");
		}
	}
}

public void
create_pier()
{
	add_cmd_item(({"into the harbour","in the harbour","in cala fasgadh", "into cala fasgadh","into the ocean","into ocean","into the water", "into water","harbour","cala fasgadh","water","off the pier",  "off pier"}),({"jump","dive"}),"@@go_tide2");
	
	add_exit(MACDUNN_DIR + "pier14", "west");
	add_exit(MACDUNN_DIR + "pier13", "north",0,0);
	add_exit(MACDUNN_DIR + "pier16", "east",0,0);    


}
