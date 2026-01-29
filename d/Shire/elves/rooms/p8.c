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
    set_short("top of mountains");
    set_long("Finally you have reached the top of a highpass through Misty " +
      "Mountains. You are in the saddle between two high peaks. " + 
      "Strong cold winds are drawing heat from you.\n");

    add_item(({"peak","peaks"}), "The peaks are high and dark. What a " +
      "relief that you don't have to climb up anymore.\n");
    add_item("saddle", "It is a natural saddle between two high peaks.\n");
    add_item("wind", "You are getting cold from it. Better go down again.\n");

    /* The other room,           direction, VBFC, fatigue */
    add_exit(ELVES_DIR+"p7", "west",    0,    10);
    add_exit(ELVES_DIR+"p9", "northeast",    0,    10);

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