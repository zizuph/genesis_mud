/**********************************************************************
 * - pie01005.c                                                     - *
 * -                                                                - *
 * - Created by Damaris@Genesis 07/Y2K                              - *
 * - ReCoded by Damaris@Genesis 03/2005                             - *
 **********************************************************************/

#pragma strict_types
#pragma save_binary
#include "../defs.h"

inherit PIER_ROOM;

#include <stdproperties.h>
#include "/d/Khalakhor/sys/paths.h"
#define VIL0905 "/d/Khalakhor/sw_speir/samorgan/room/vil0905"
object *workers;

public int *
query_local_coords()
{
	return ({10, 5});
}

public int
block_exit()
{
	write("There is no way to cross to the beach. The other "+
        "end of the pier has been washed away by a storm, which "+
        "makes the shore inaccessible.\n");
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
          workers[i] = clone_object(NPC + "worker");
          if (i == 0)
            {
              workers[i]->set_team_leader();
            }
          else
            workers[i]->set_team_follower();
          workers[i]->set_team_name("worker_team");
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
	add_exit(VIL0905, "north");
	add_exit("pie1105", "south");
	set_alarm(0.5, 0.0, reset_room);
}
