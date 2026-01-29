#include "defs.h"
#include "/sys/ss_types.h"

inherit "/d/Shire/room";

create_room() {
    set_short("Forest");
    set_long(break_string(
	  "You are in the very heart of this old and wise forest. "
	+ "This seems to be the place towards which the forest is pushing "
	+ "you. Before you stands a tall, old willow.\n",70) 
        + "There are no obvious exits.\n");

    add_item(({"tree","willow","willow tree"}), break_string(
	  "The willow tree is a very old tree. Something seems to be "
	+ "shining from its top.\n",70));

    add_item("trees", break_string(
	  "The trees seem to be looking straight at you, and you feel "
	+ "frightened by them. You can only fix your mind on getting out "
	+ "of here as soon as possible.\n",70));

    add_item(({"branch","branches"}), break_string(
	  "The branches of the trees seem to come in your direction "
	+ "whenever you pass them. They are quite scary.\n",70));

    add_item("top", break_string(
          "You cannot quite make up what is shining from the top, perhaps "
        + "you should climb in the willow to see what is there.\n",70));
}

init() {
    ::init(); 
    add_action("do_climb","climb");
    add_action("do_sleep", "sleep");
    add_action("do_sleep", "rest");
}

do_climb(str) {
    object tp;
    int skill;

    if(str == "willow" || str == "willow tree" || str == "tree" || str == "up")
    {
	tp = this_player();
        skill = tp->query_skill(SS_CLIMB);

	/* Give inexperienced climbers some change in succeeding */
	if (skill < 10 && skill < random(50))
	{
	    write(break_string(
		  "You are not experienced enough in climbing to climb "
		+ "the willow. You get some feet off the ground, but then "
		+ "you suddenly lose grip and fall down. After a rough "
		+ "landing on your head, you pass out. Just before you "
		+ "lose your consciousness, you think you hear someone "
		+ "singing in the distance.\n",70));

	    tp->move_living("M", STAND_DIR + "unconscious");
	}
	else
	{
	    /* Let fortunate, but inexperienced climbers gain a skilllevel */
	    if (skill < 10)
	    {
		tp->set_skill(skill + 1);
	    }
            write("You climb up the tree.\n"
		+ "Suddenly you are stuck!!\n");
	    this_player()->move_living("M", STAND_DIR + "forest5"); 
	}
        return 1; 
    }
}
do_sleep(){
    {
    write("You feel very tired, and lie down for a rest in the comforting\n" +
          "shadow of the old willow. You don't wake till it's to late..\n");
          this_player()->move_living("M", STAND_DIR + "forest5");
         }
   return 1;
}
