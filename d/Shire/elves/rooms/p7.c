/* highpass */

#include "local.h"

inherit SHIRE_ROOM;
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "east";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

void
create_shire_room()
{
    set_short("at slope");
    set_long("You are climbing the slope of Misty Mountains. Above you " + 
             "can see the top of it. There is also a big crack in the " + 
             "mountain to the south.\n");

    add_item("crack", "It is really big. Nearly like a small canyon. A " +
               "soft breeze blows from the crack, bringing the smell of " +
               "damp earth and something else you can't quite identify.\n");

              /* The other room,           direction, VBFC, fatigue */
    add_exit(ELVES_DIR+"p6", "northwest",    0,    10);
    add_exit(ELVES_DIR+"p8", "east",    0,    10);


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