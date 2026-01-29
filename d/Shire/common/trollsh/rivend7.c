/* File: /d/Shire/common/trollsh/rivend7.c */

#include "defs.h"
#include <ss_types.h>
inherit "/d/Shire/common/lib/eastroad";	/*master object*/
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "w";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

#define MAX_TROLLS 3

static object *trolls = allocate(MAX_TROLLS);

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	    "You are walking on a path in the Trollshaws. "+
	    "You can hear the sound of a river, but "+
	    "since the forest is so dense here you can not "+
	    "see the river yet. There are trees all around "+
	    "blocking your view in all directions. The only "+
	    "break in the trees is the path going west and east.\n");

    add_item(({"eastroad", "road" }),
        "The road is wide and seems to be in constant use.\n");
    add_item(({"gravel"}),
	    "The gravel is rough and covers the road.\n");
    add_item(({"large trees", "trees"}),
        "Various tall firs and deciduous trees grow alongside " +
        "the road. They are tall, blocking the sky.\n");
    add_item("stunted trees",
        "They grow in various spots, dwarfed by their taller " +
        "neighbors. The stunted trees look like they have " +
        "survived the roughest treatment and defy the elements.\n");
    add_item("tracks", "@@exa_tracks");
    add_exit(STAND_DIR + "rivend8", "east", 0);
    add_exit(STAND_DIR + "rivend6", "west", 0);

    reset_shire_room();
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
string
exa_tracks()
{
    if (TP->query_skill(SS_TRACKING) > 40)
	return "The tracks look like troll tracks.\n";
    else
	return "They look big!\n";
}


void
reset_shire_room()
{

    int index;

    /* Do this first, since we may need to clone. */
    setuid();
    seteuid(getuid());

    /* Loop over all elements in the array. */
    for(index = 0; index < MAX_TROLLS; index++)
    {
        if (!objectp(trolls[index]))
        {
            trolls[index] = clone_object(TROLLSH_DIR+ "npc/trollet");
            trolls[index]->set_restrain_path(({TROLLSH_DIR}));
            trolls[index]->set_random_move(3);
            trolls[index]->set_monster_home(TROLLSH_DIR + "mpath2");
            trolls[index]->move(TO);

        }
    }
}
