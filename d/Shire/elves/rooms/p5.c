/* highpass */

#include <ss_types.h>
#include "local.h"

inherit SHIRE_ROOM;
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "east";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

void
create_shire_room()
{
    add_prop(ROOM_I_INSIDE, 0);
    set_short("at slope");
    set_long("You are climbing the slope of Misty Mountains. You are " +
             "really tired and wonder how long you will have to climb " +
             "up till you reach the top. Or are you going down??? It " +
             "seems that you are so tired that you forget which way you " +
             "want to go.\n");


              /* The other room, direction, VBFC, fatigue */
    add_exit("p4", "west",    0,    0);
    add_exit("p6", "east",    0,    0);

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