/* File: /d/Shire/common/eastroad/mpath1 */

#include "defs.h";

inherit "/d/Shire/common/lib/rom";
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "s";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

create_rom()
{
    set_short("On the Great East Road near the Trollshaws");
    set_long("You are walking on the Great East Road near the river " +
        "Bruinen. To the west is the great forest Trollshaws. " +
        "The forest is very thick, so you can not see more than " +
        "a few yards through it. Upstream, you hear strange " +
        "sounds from the forest. You had better stay within " +
        "sight of the river.\n");

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

    NORTH("mpath2");
    SOUTH("rivend9");    
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