/* File: /d/Shire/common/trollsh/rivend5.c */
#include "defs.h"
inherit "/d/Shire/common/lib/eastroad";	/*master object*/
#define NEED_CLIMB_SKILL    15

void up_tree();

object troll;

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	    "You are walking in the middle of the great forest Trollshaws. "+
	    "This is a dark and gloomy place. The sun seldom or never shines "+
	    "here.\n");

    add_item(({"eastroad", "road" }),
	    "The road is narrow, about 2 meters wide and seems to be used a lot.\n"
    );
    add_exit(TROLLSH_DIR + "rivend6", "northeast", 0);
    add_exit(TROLLSH_DIR + "rivend5", "southwest", 0);

}

public void
init()
{
    ::init();
    add_action("do_climb", "climb");
}

int do_climb(string str)
{
    int player_climb_skill;
    if(!str)
    {
        write("Climb what? \n");
        return 1;
    }

    player_climb_skill = TP->query_skill(SS_CLIMB);

    if(str =="tree" || str == "branch")
    {
        write("Do you want to climb up or down?\n");
        return 1;
    }

    if(str=="up")
       {
           up_tree();
       }

    else write("Climb what?\n");
    return 1;
}

void
up_tree()
{
    write("You reach up and grab an overhanging branch and pull " +
        "yourself up. With a great deal of effort, you climb " +
        "several branches and go up into a tree.\n");
    say(QCTNAME(TP) + " reaches up and grabs an overhanging branch. " +
        "With a great deal of effort, " + CAP(HE_SHE(TP)) + " climbs " +
        "several branches and climbs up into a tree.\n");
    TP->move_living("M",TROLLSH_DIR + "troll_tree01");
    tell_room(ENV(TP), QCTNAME(TP) + " arrives from below.\n",TP);
}

