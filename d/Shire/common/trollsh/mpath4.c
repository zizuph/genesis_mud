/* File: /d/Shire/common/eastroad/mpath4 */

#include "defs.h"
#include <ss_types.h>

inherit "/d/Shire/common/lib/rom";
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "sw";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

#define MAX_TROLLS 4

static object *trolls = allocate(MAX_TROLLS);

#define GER "/d/Shire/eastroad/eastern/"
#define TROLLS_DIR "/d/Shire/common/trollsh/"
create_rom()
{

    set_short("On the Great East Road near the Trollshaws");
    set_long("You are walking on the Great East Road near the " +
		"river Bruinen. As you turn northeast you leave the " +
		"Trollshaws behind you. The area around you is becoming " +
		"solid rock with only a muddy path by the river side.\n");

    add_item(({"path", "path", "great east road", "road"}),
        "This is a road by the river Bruinen. The road follows " +
        "the river upstream.\n");
    add_item(({"river","bruinen","water"}),
        "This is the mighty river Bruinen. It doesn't seem " +
        "possible to cross here, maybe further north.\n");
    add_neg(({"swim", "enter", "dive", "jump"}),
        "[into] [in] [over] [across] [the] 'river' / 'bruinen' / 'Bruinen'",
        "You notice that the water is freezing cold, hence, you " +
        "would not even try it.\n");

    add_item(({"mud"}),
        "This is a brown sticky mud. It's obviously made by the " +
        "water from the Bruinen.\n"); 
    add_exit(GER + "imladris_connect", "north", "@@tree_north@@");
    add_exit(TROLLS_DIR + "mpath3", "southwest", "@@tree_southwest@@");

    reset_shire_room();
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


void tree_north()
{
    tell_room("/d/Shire/eastroad/eastern/riv_bushes.c", QCTNAME(TP) +
    " headed south towards the Trollshaws.\n");
}

void tree_southwest()
{
    tell_room("/d/Shire/eastroad/eastern/riv_bushes.c", QCTNAME(TP) + 
    " went north into the Misty Mountains.\n");
}
