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
	     "To your east you can see the center of the village, which " +
	     "seems to be some kind of large open area. North of " +
	     "you is a stone building, but which cannot be accessed from " +
	     "this side. Northwest and south you can see " +
	     "several tents, homes of the common people in Que Kiri. " +
	     "To your west you can see an opening in the wall, where the " +
	     "path leads outside the village onto the Plains of Abanasinia.\n");
    set_change_msg(0,ATTACK);
    set_change_short(1,"On a path in the burning Que Kiri");
    set_change_long(1,"You are standing on a path in the village of Que Kiri. " +
		    "All around you, there is smoke, fires and chaos. To your " +
		    "north, there are remains of something " +
		    "that could have been a building. East of you is a large " +
		    "blackened open area. To the west you can see the entrance " +
		    "into the village, the wall looks broken everywhere.\n");
    set_change_msg(1,SMOLDER);
    set_change_short(2,"On a path in the burnt Que Kiri");
    set_change_long(2,"You are standing on a path in the village of Que " +
		    "Kiri. All around you, there are smoldering ashes and " +
		    "everything blackened from a fire. To your north, there " +
		    "are remains of something that could have been a " +
		    "building. East of you is a large blackened open area. " +
		    "To the west you can see the entrance into the village, " +
		    "the wall looks broken everywhere.\n");
    set_change_msg(2,REBUILD);
    set_change_short(3,"On a path in Que Kiri");
    set_change_long(3,"You are standing on a path in the village of Que Kiri. " +
		    "Around you, work on the village is in progress. A half-" +
		    "finished building is to your north and a few tents are " +
		    "visible northwest and south, but there are still a lot of " +
		    "empty spots. East of you is a large open area, and to " +
		    "your west you can reach a wall, where the path leads out of " +
		    "the village onto the Plains of Abanasinia.\n");
    set_change_msg(3,FINISH);
    
    OUTSIDE;

    add_exit(ROOM + "arena","east");
    add_exit(ROOM + "tent2","northwest");
    add_exit(EAST_EXIT,"west");
    add_exit(ROOM + "tent4","south");
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
