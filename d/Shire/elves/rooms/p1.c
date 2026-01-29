/* highpass */

#include "local.h"
// #include "/d/Shire/sys/flags.h"

inherit SHIRE_ROOM;
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "east";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

void
create_shire_room()
{
    set_short("valley");
    set_long("You are in the valley which goes east straight towards the " +
      "Misty Mountains. Its green vegetation is a big contrast to "+
      "the dark grey colours of the peaks. To the west, the valley "+
      "goes towards the Great East "+
      "Road.\n");

    add_item("valley", "This is a fair green valley. It is mostly filled with "+
      "green bushes. It is nice and peaceful here although "+
      "the nearby mountains reminds you that there may be " +
      "danger close.\n");
    add_item("vegetation", "The valley is mostly filled with the green bushes.\n");
    add_item("mountains", "The mountains look somehow dark. Maybe there is " +
      "danger brooding there.\n");
    add_item(({"bushes", "bush"}), "You see ordinary green " +
        "bushes all around. They all seem healthy even though " +
        "they look scraggly.\n");

    /* The other room,           direction, VBFC, fatigue */
    add_exit(ELVES_DIR + "p9", "west", 0, 2);
    add_exit(ELVES_DIR + "p2", "east",    0,    3);

    
    add_npc("/d/Shire/elves/elfmaker.c", 5);
add_npc("/d/Shire/elves/elf.c");

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

