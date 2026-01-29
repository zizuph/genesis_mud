/* highpass */

#include "local.h";

inherit SHIRE_ROOM;
inherit IS_ELF_GR_TRAVELLER;


static string  patrol_dir = "northeast";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

void
create_shire_room()
{
    add_prop(ROOM_I_INSIDE, 0);
    set_short("at foot of mountains");
    set_long("You are at the foot of Misty Mountains. To the west you " + 
      "see the valley with paths going towards the lowlands " + 
      "of Rhudaur and to northeast it climbs up a steep slope.\n");


    add_item("valley", "You see a fair green valley.\n");
    add_item("mountains", "The mountains look somehow dark. Maybe there is " +
      "danger brooding there.\n");

    /* The other room,           direction, VBFC, fatigue */
    add_exit(ELVES_DIR+"p1", "west",    0,    3);
    add_exit(ELVES_DIR+"p3", "northeast",    0,    4);

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
