/*
  Whislte for calling bandit
  by Udana, /06
*/

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

int charges = 5 + random(5);

create_object()
{
	set_name("whistle");
	add_name("pipe");
	set_short("long black whistle");
	set_long("A ten-inch long, thin pipe made of black wood. You could " +
            "probably signal someone, even from far away, by blowing it.\n");
	add_prop(OBJ_M_NO_SELL, "The whistle has no value.\n");
	add_prop(OBJ_M_NO_DROP, "Dropping the whistle isn't such a good idea.\n");
	add_prop(OBJ_M_NO_GIVE, "You can't give the whistle away.\n");
	add_prop(OBJ_M_NO_STEAL, 1);
	add_prop(OBJ_I_WEIGHT, 100);
	add_prop(OBJ_I_VOLUME, 50);
	add_prop(OBJ_I_VALUE, 0);
}

public void init()
{
	::init();
	add_action("call_bandits", "signal");
	add_action("call_bandits", "blow");
}

void bandits_here(object ob)
{
	E(E(TO))->bandit_ambush(ob);
}

int call_bandits(string a)
{
	if(query_verb() == "blow")
		if(!strlen(a) || a != "whistle")
		{
			notify_fail("Blow what? Whistle maybe?\n");
			return 0;
		}
	write("You blow on the whistle, making high vibrating sound.\n");
	say(QCTNAME(TP) + " blows on his whistle, making high vibrating sound.\n");
	if(!objectp(TP->query_attack()))
		write("Since you're not fighting anyone, signaled allies, wouldn't know "+
			"who you want them to attack.\n");
	else
	{
		if(charges)
		{
			charges--;
			set_alarm(1.0, 0.0, &bandits_here(TP->query_attack()));
		}
		else
		{
			write("The whistle suddenly breaks!\n");
			remove_object();
		}
	}
	return 1;
}
