/* created by Aridor 12/01/93 */

inherit "/std/room";

#include "clubdefs.h"

object rankdev;

create_room()
{
    set_short("Private Club Lounge");
    set_long(BS("You are standing in a very comfortable room. Carpets " +
		"displaying battle scenes drown out noises and the tapestries " +
		"on the walls let you relax in your own memories of battles " +
		"and adventures. A very comfortable looking sofa with some kind " +
		"of bar next to it adorns the north wall. The west wall displays a very odd " +
		"plain surface, but which is rather reassuring. Maybe you should " +
		"take a closer look?",SL));

    INSIDE;
    LIGHT;

    add_item(({"knights","battle","battle scene","battle scenes","monsters","knight","monster"}),
	     BS("They are woven into the carpets, otherwise you cannot make out anything special.",SL));
    add_item(({"carpet","carpets","floor"}),
	     BS("The floor is covered with soft carpets, the carpets displaying " +
		"battle scenes. You can make out good knights fighting evil " +
		"monsters.",SL));
    add_item(({"tapestries","tapestry"}),
	      BS("The tapestries show scenes from adventures, you can see a " +
		 "crystal tower, a huge mansion, a castle on top of a mountain. " +
		 "There are adventurers just like you standing there, displaying " +
		 "loot and treasures.",SL));
    add_item(({"sofa"}),
	     BS("It's a very comfortable looking sofa.",SL));
    add_cmd_item(({"on sofa","sofa","down"}),"sit",
		 BS("You sit down on the sofa and immediately feel very relaxed.",SL));
    add_item(({"bar"}),
	     BS("It's a small bar, but unfortunately the squires must have forgotten to " +
		"put drinks in it. Go easy on the squires, and instead get yourself " +
		"a drink in the Silver Dragon Inn of Palanthas. You may even want to " +
		"talk to the proprietor there, he may have some work for you to do.",SL));

    add_exit(CLUB + "club3","east");

    reset_room();
}


reset_room()
{
  if (!rankdev)
    {
      rankdev = clone_object(CLUB + "rankdevice");
      rankdev->move(TO);
    }
}
