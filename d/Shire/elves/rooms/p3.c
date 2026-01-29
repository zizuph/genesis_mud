/* highpass */

#include "local.h"

inherit SHIRE_ROOM;
inherit IS_ELF_GR_TRAVELLER;


static string  patrol_dir = "northeast";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

void
create_shire_room()
{
    set_short("below rock");
    set_long("You are climbing the slope of Misty Mountains. Above you " +
      "there is a big rock which is exactly in your way upwards. You may " + 
      "pass it to the east or northeast. There is no way to tell which " + 
      "is the right road.\n");


    add_item("rock", "It is big and dark. No way to pass it except " + 
      "walk around.\n");
    add_item(({"road"}),
        "It is is rocky, windy its way through the mountains.\n");

    add_exit(ELVES_DIR+"p2", "southwest",    0,    4);
    add_exit(ELVES_DIR+"p4", "northeast",    0,    5);
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


