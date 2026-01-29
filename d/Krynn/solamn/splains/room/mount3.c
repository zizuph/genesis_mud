/* created by Aridor 12/20/93 */

#include "../local.h"
#include <ss_types.h>

inherit OUTSIDE_BASE;

/*prototype*/
string jump_to_the_rock();

void
create_splains_room()
{
    set_short("At the foot of the mountains");
    set_long(BS("Impressive mountains rise up right to your west and northwest. " +
		"The plains stretch out to your east as far as you can see. " +
		"There is a river blocking your path north. The river " +
		"is coming out of the narrow " +
		"valley to your west and flowing onto the plains southeast. You are " +
		"still on the plains, and the grass is just as dry as everywhere " +
		"else, since the level of the river is just too low. Beyond the " +
		"river in the northeast the plains continue, but you can't get across " +
		"the river.",SL));

    add_item(({"mountain","mountains","cliff"}),
	     "The mountains you see rise up direct in front of you to your west. " + 
	     "The mountain range runs in " +
	     "a southwest - northeastern direction. The cliff looks impossible to " +
	     "climb.\n");
    add_item(({"river"}),
	     "It's not a very wide river, and the waterlevel is much lower than the " +
	     "plains. The river comes from a narrow valley to your northwest and flows " +
	     "north of you and to the east onto the plains.\n");
    add_item(({"valley","gorge"}),
	     "The valley is so narrow that there is only room for the river and it " +
	     "looks impossible to go in on foot. However, you notice a big rock lying " +
	     "in the middle of the river in the gorge.\n");
    add_item(({"rock","big rock"}),
	     "It is a big rock lying in the middle of the river. The top level of the rock is " +
	     "at about the same level as the plains are. It's not unreachable either " +
	     "if you dare to jump.\n");
    add_item(({"side","other side","beyond","beyond river","beyond the river"}),
	     "The plains across the river look exactly like these, so why would " +
	     "you want to go there?\n");
    add_item(({"grass","plains"}),
	     "There is brown grass here on the plains, but you think " +
	     "the ground might just be a little damper here near the river.\n");
    add_cmd_item(({"mountain","cliff","mountains"}),"climb",
		 "You can't do that, it is just too steep.\n");
    add_cmd_item("river",({"swim","enter"}),
		 "The plains across the river look exactly like these, so why would " +
		 "you want to go there?\n");
    add_cmd_item(({"rock","big rock","to rock","to big rock","to the rock","to the big rock","over to the rock","over to the big rock"}),
		 "jump","@@jump_to_the_rock");

    set_noshow_obvious(1);
    add_exit(ROOM + "plain18","south",0,3);
    add_exit(ROOM + "river1","east",0,3);
    add_exit(ROOM + "mount2","southwest",0,3);

}


string
jump_to_the_rock()
{
  if (TP->query_stat(SS_DEX) < random(20) + 20)
    {
      write("You fall into the water.\n");
      TP->move_living("falling down",ROOM + "in_water",1,1);
    }
  else
    {
      write("You make it on top of the rock.\n");
      TP->move_living("in a big jump",ROOM + "on_rock",1,0);
    }
  return "";
}
