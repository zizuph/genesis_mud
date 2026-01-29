/* File: /d/Shire/common/eastroad/mpath2 */

#include "defs.h"
#include <ss_types.h>

inherit "/d/Shire/common/lib/rom";
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "s";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

#define MAX_TROLLS 2

static object *trolls = allocate(MAX_TROLLS);

create_rom()
{

    set_short("On the Great East Road near the Trollshaws");
    set_long("Walking on the Great East Road, by the river " +
		"Bruinen, you notice to the west is the great forest " +
		"Trollshaws. It is said that the forest is packed with " +
		"trolls. Up the path you notice some giant footprints " +
		"in the mud. The footprints come from the forest and " +
		"head down towards the riverbank.\n");
    add_item(({"path", "path", "great east road", "road"}),
        "This is a road by the river Bruinen. The road follows " +
        "the river upstream.\n");
    add_item(({"river","bruinen","water"}),
        "This is the mighty river Bruinen. It doesn't seem " +
        "possible to cross here, maybe further south.\n");
    add_neg(({"swim", "enter", "dive", "jump"}),
        "[into] [in] [over] [across] [the] 'river' / 'bruinen' / 'Bruinen'",
        "You notice that the water is freezing cold, hence, you " +
        "would not even try it.\n");
    reset_shire_room();

    add_item(({"prints","footprints"}),
	"@@exa_prints@@");

    NORTH("mpath3");
    SOUTH("mpath1");
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
exa_prints()
{
    if (TP->query_skill(SS_TRACKING) +
        TP->query_skill(SS_AWARENESS) + random(50) > 150)
	return "They look like footprints from a troll. It seems like the\n"
             + "troll had a big fight here, and was victorious. It\n"
             + "seems like the troll had been dragging something after it.\n";
    else if (TP->query_skill(SS_TRACKING) + TP->query_skill(SS_AWARENESS) > 60)
        return "You are pretty sure they are troll prints!\n";
    else
	return "They look like large footprints!\n";

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


