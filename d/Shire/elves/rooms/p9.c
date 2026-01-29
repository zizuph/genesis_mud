/* highpass */

#include "local.h"

inherit SHIRE_ROOM;
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "southeast";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

void
create_shire_room()
{
    set_short("at slope");
    set_long("You are climbing the slope of the Misty Mountains. Above you " + 
      "can see the top of it.\n");

    /* The other room,           direction, VBFC, fatigue */
    add_exit(ELVES_DIR+"p8", "southwest",    0,    10);
    add_exit(ELVES_DIR+"p1", "southeast",    0,    10);

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