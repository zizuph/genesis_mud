#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "nw";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }


void
create_er_room()
{
    set_area("the Last Bridge of");
    set_areaname("the Great East Road");
    set_land("Eriador");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("river,");
    set_grass("lush, green");
    set_treetype("willow");

    set_extraline("The Hoarwell river roars and rumbles along its "+
    "merry way below you, but you're secure in the fact that this "+
    "bridge of many millenia and the sturdiest build will provide "+
    "safe passage for a long time to come. Looking northwest past "+
    "the riverside willows you can make out the dry downs of the "+
    "Lone-lands, and to the southeast the forest thickens and "+
    "darkens as you enter Rhudaur, the Trollshaws. "+
    "The road continues to the northwest and southeast from here.");

add_item(({"southeast","rhudaur","trollshaws","forest"}),
"The road meanders southeast off the bridge and bravely "+
"on into the Trollshaws, the ancient forest of Rhudaur, "+
"named after trolls with good reason.\n");
add_item(({"hoarwell","river","hoarwell river"}),
"Rushing and peaking in its hurry southwest, the great Hoar"+
"well river seems to carve its way along an avenue of "+
"weeping willows, challenged only by a span that must be "+
"the \"Last Bridge\".\n");
add_item(({"bridge","span","last bridge"}),
"The ancient stone bridge, known as the Last Bridge, "+
"here dares challenge the Hoarwell's fury, its foundations "+
"seemingly immovable by river or time. Massive, smooth "+
"blocks of granite form a span easily wide enough for two "+
"wagons to pass by each other.\n");
add_item(({"trees","willows"}),
"The shade and nourishment provided by the river valley "+
"gives bloom to a healthy run of willows and other trees"+
", and on the east side of the river the forests thicken "+
"and become the dreaded Trollshaws.\n");
add_item(("foundation"),
"A small dirt trail runs down to the foundations on the "+
"southeastern bank.\n");
add_item(("trail"),
"It appears to be a seldom used trail by the looks "+
"of the brush growing over it. It meanders its way "+
"down to the banks of the river. Perhaps you can "+
"follow it?\n");

    add_exit(ER_DIR + "erb37",  "northwest", 0, 1);
    add_exit(TS_DIR + "rivend1",  "southeast", 0, 1);
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

/*
int
do_follow(string s)
{
    object *team = ({});
    int i, sz;

    if (!stringp(s) || s != "trail")
        return 0;

    team = TP->query_team();
    team += ({ TP });
    sz = sizeof(team);
    for (i = 0; i < sz; i++)
    {
        if (present(team[i], TO))
        {
            team[i]->catch_tell("You make your way down to "+
            "the river bank.\n");
            team[i]->move_living("M","/d/Shire/common/trollsh/new/bank",1,0);
        }
    }

    return 1;
}

void
init()
{
    ::init();

    add_action(do_follow,"follow");
}
*/
