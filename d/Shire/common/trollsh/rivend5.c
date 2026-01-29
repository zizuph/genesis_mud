/* File: /d/Shire/common/trollsh/rivend5.c */
#include "defs.h"
inherit "/d/Shire/common/lib/eastroad";	/*master object*/

inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "w";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

#define NEED_CLIMB_SKILL    15

void up_tree();

object troll;

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	    "You are walking in the middle of the great forest Trollshaws. "+
	    "This is a dark and gloomy place. Scary animal noises can be heard "+
	    "throughout the forest. Large and stunted trees grow everywhere.\n" );

    add_item(({"eastroad", "road" }),
	    "The road is narrow. It looks like there have been little traffic "
	    +"on the road.\n");

    add_item(({"large trees", "trees"}),
        "Various tall firs and deciduous trees grow alongside " +
        "the road. They are tall, blocking the sky. One tall tree stands " +
        "out from the others.\n");
    add_item("stunted trees",
        "They grow in various spots, dwarfed by their taller " +
        "neighbors. The stunted trees look like they have " +
        "survived the roughest treatment and defy the elements.\n");
    add_item(({"tall tree"}),
        "The tall tree stands away from the road. Some of its branches " +
        "reach low enough to the ground that you can probably climb " +
        "the tree.\n");
    

    add_exit(TROLLSH_DIR + "rivend5a", "northeast", 0);
    add_exit(TROLLSH_DIR + "rivend4", "west", 0);

}


public void
enter_inv(object ob, object from)
{
	string *names;
	::enter_inv(ob, from);
	names = ob->query_names();
	if(ob->id(npc_name))
	{
		if (!move_alarm || !sizeof(get_alarm(move_alarm)))
		{
			move_alarm = set_alarm(50.0 + rnd() * 20.0, 0.0, &move_patrol(ob));
		}
	return;
	}
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
