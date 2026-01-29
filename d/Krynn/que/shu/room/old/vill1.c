/* Started by Gorret,
 * continued by Erine,
 * finished by Aridor
 * 07/95 
 */

#include "../local.h"
inherit ATTACKROOM;
#include RND_MEET

object monster;

void
create_attack_room()
{
    set_short("On a path in Que Kiri");
    set_long("You are standing on a path in the village of Que Kiri. " +
	     "To your south you can see the center of the village, which " +
	     "seems to be some kind of large open area. Southeast of " +
	     "you is a stone building, northeast and east you can see " +
	     "several tents, homes of the common people in Que Kiri. " +
	     "To your north you can see an opening in the wall, where the " +
	     "path leads outside the village onto the Plains of Abanasinia. " +
	     "West of you is another stone building, apparently the home " +
	     "of an important person.\n");
    set_change_msg(0,ATTACK + "@@add_exit|" + (ROOM + "chief") + "|west@@");
    set_change_short(1,"On a path in the burning Que Kiri");
    set_change_long(1,"You are standing on a path in the village of Que Kiri. " +
		    "All around you, there is smoke, fires and chaos. To your " +
		    "southeast and to your west, there are remains of something " +
		    "that could have been buildings. South of you is a large " +
		    "blackened open area. To the north you can see the entrance " +
		    "into the village, now the entire wall has been torn down " +
		    "and the entrance is about 10 times as wide as normal.\n");
    set_change_msg(1,SMOLDER);
    set_change_short(2,"On a path in the burnt Que Kiri");
    set_change_long(2,"You are standing on a path in the village of Que Kiri. " +
		    "All around you, there are smoldering ashes and everything " +
		    "blackened from a fire. To your " +
		    "southeast and to your west, there are remains of something " +
		    "that could have been buildings. South of you is a large " +
		    "blackened open area. To the north you can see the entrance " +
		    "into the village, now the entire wall has been torn down " +
		    "and the entrance is about 10 times as wide as normal.\n");
    set_change_msg(2,REBUILD);
    set_change_short(3,"On a path in Que Kiri");
    set_change_long(3,"You are standing on a path in the village of Que Kiri. " +
		    "Around you, work on the village is in progress. A half-" +
		    "finished building is to your west and another partly " +
		    "finished building is to your southeast. A few tents are " +
		    "visible further east, but there are still a lot of empty " +
		    "spots. South of you is a large open area, and to your " +
		    "north you can reach a wall, where the path leads out of " +
		    "the village onto the Plains of Abanasinia.\n");
    set_change_msg(3,FINISH + "@@remove_exit|west@@");
    
    OUTSIDE;

    add_exit(ROOM + "arena","south");
    add_exit(ROOM + "tent1","northeast");
    add_exit(SOUTH_EXIT,"north");
    /*add_exit(ROOM + "chief","west");*/
    add_exit(ROOM + "temple","southeast");
}

string
tent_desc()
{
    switch(QUERY_STATE)
      {
	case 0: return ("");
	case 1: return ("");
	case 2: return ("");
	case 3: return ("");
	default: return 0;
      }
}
