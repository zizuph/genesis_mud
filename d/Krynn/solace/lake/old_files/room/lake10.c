/* created by Splunge, modified by Aridor */

#include <ss_types.h>
#include "../local.h"
#include <tasks.h>

inherit SOLACE_ROOM_BASE;

void
create_solace_room()
{
    set_short("Dead End");
    set_long("This is a dead end. It seems that the road " +
      "just stops here. The trees have been completely " +
      "cleared up to the end of the path.\n");
    add_item(({"path","road"}),
      "There isn't really much to look at. It stops pretty quick...\n");
    add_item(({"trees","tree"}),
      "There are a lot of trees. It must have taken whoever made " +
      "this quite some time to clear this road. Among these, you " +
      "take notice of one tree of enormous proportions.\n");
    add_item("brush",
      "You see a few rabbits and mice scurrying around in the brush, " +
      "but not much else.\n");
    add_item(({"big tree","large tree","enormous tree"}),
      "You see a small bird in this tree.\n");
    add_item(({"small bird","bird"}),
      "You can't see him very well...He is very high up.\n" +
      "Perhaps you should call him?\n");
    add_cmd_item(({"bird","small bird","to bird","at bird","at small bird",
	"to large bird"}), ({"call","whistle","sing","yell"}),
      "@@follow_bird");
    add_exit(ROOM + "lake9","east",0);
}

string
follow_bird()
{
    if (TP->query_skill(SS_ANI_HANDL) > 25 && TP->resolve_task(TASK_ROUTINE,
	SS_ANI_HANDL) > 0)

    {
	write("You whistle the standard call to the bird. He " +
	  "seems to relax. Then, he flutters up to you and " +
	  "lands on your shoulder. It seems he wants to tell " +
	  "you something... As you watch, he flits to a tree, and " + 
	  "then another tree, and then another. You gasp as you " +
	  "discover that this little bird has shown you a path " +
	  "through the thick trees towards the north!\n\n");
	write("You pass through the incredibly dense foliage. " +
	  "Only able to continue because of the bird's knowledge. " +
	  "There are many pits and traps interspersed throughout " +
	  "this area, and you are very careful to follow the bird " +
	  "closely. Suddenly, the birds grow totally silent as a " +
	  "roar rips through the dark trees. Your guide flies away " +
	  "quickly, terrified of the sound. You are on your own now.\n");
	TP->move_living("following the bird",ROOM + "lake11",1,0);
    } 
    else 
	write("Come to think of it, you haven't got the faintest idea how to " +
	  "call a bird.\n");
    return "";
}
