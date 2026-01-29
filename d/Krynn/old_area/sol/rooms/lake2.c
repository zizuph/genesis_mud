/*   Crystalmir - Lakeside Road #2
     Splunge - Krynn  Jan. 20, 1994  */

#include "../local.h";

inherit SWIM_ROOM;

#include <ss_types.h>

void
create_swim_room() 
{
    set_long("As you walk further along the beaten dirt road, your " +
	     "apprehension does not let up any. Sure, the scenery is " +
	     "great, but that doesn't seem to matter to you. The talk back " +
	     "in the village has put you on edge.\n");
    add_item("road",
	     "This rough dirt road follows alongside Crystalmir Lake. It " +
	     "seems like there has been a lot of traffic through here " +
	     "recently.\n");
    add_item(({"army"}),
	     "You can't see anything, but that is not nessesary. You aren't " +
	     "stupid.\n");
    add_item("mountains",
	     "The mountains on the other side of the lake look majestic and " +
	     "inspiring. You sigh deeply, hoping beyond hope to LIVE to " +
	     "visit them some day.\n");
    add_item("wilderness",
	     "Just kidding about the wilderness soothing your soul. This " +
	     "place gives you the creeps. It's dark and nasty. The woods " +
	     "to the east of you seem to have eyes, and you walk along the " +
	     "path with your guard up.\n");
    add_exit(ROOM + "lake1","south",0,3);
    add_exit(ROOM + "lake3","northwest","@@check_lev",3);
}

int
check_lev()
{
    if (TP->query_stat(SS_DIS) < 30)
      { 
	  write("You don't have the self-discipline to continue any " +
		"further this way.\n");
	  return 1; 
      }
    return 0;
}

void
enter_inv(object to, object from)
{  
    (ROOM + "lake3.c")->load_me();
    ::enter_inv(to, from);
}
