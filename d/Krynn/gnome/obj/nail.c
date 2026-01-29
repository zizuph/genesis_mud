inherit "/std/object";

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>

void
create_object()
{
	set_name("nail");
	add_name("lian");
	set_short("nail");
	set_adj("old");
	add_adj("rusty");
	set_long("An old and rusty nail. Nevertheless it would be still "
		 + "usable, if it wasn't that terribly "
		 + "bent in the middle.\n");
	add_prop(OBJ_I_WEIGHT, 10);
	add_prop(OBJ_I_VOLUME, 1);
	add_prop(OBJ_I_VALUE, 0);
}

void
init()
{
	ADD("do_straight", "bend");
	ADD("do_straight", "straighten");
	ADD("do_hammer", "hammer");
}

void
is_straight(object player)
{
	player->catch_msg("You successfully straightened out the nail!\n");
	tell_room(E(player), QCTNAME(player) + " ceases hammering with a content "
		+ "smile on " + POSSESSIVE(player) + " face.\n", player);
	set_long("An old and rusty nail. It looks still "
		 + "usable though.\n");
	add_name("nail_for_sign");
}

int
do_hammer(string str)
{
	NF("Hammer what?\n");
	if (str != "nail" && str != "on nail")
		return 0;
	if (present("hammer", TP))
	{
		write("You hammer a little...\n");
		say(QCTNAME(TP) + " hammers a little on " + POSSESSIVE(TP)
			+ " nail.\n");
		set_alarm(5.0, -1.0, "is_straight", TP);
		return 1;
	}
	NF("You try, but fail. Perhaps you should use a suitable tool?\n");
	say(QCTNAME(TP) + " does something to " + POSSESSIVE(TP)
		+ " nail but achieves nothing.\n");
	return 0;
}

int
do_straight(string str)
{
	NF("Do what?\n");
	if (str != "nail" && str != "nail with hammer") 
		return 0;
	{
	if (str == "nail")
	{
		write("You scratch yourself on the rusty nail. "
			+ "Perhaps you should use a tool?\n");
		return 1;
	}
	NF("You have no hammer.\n");
	if(!(present("hammer", TP)))
		return 0;
	write("You hammer a little...\n");
	say (QCTNAME(TP) + " hammers a little on " + POSSESSIVE(TP)
		+ " nail.\n");
	set_alarm(5.0, -1.0, "is_straight", TP);
	return 1;
	}
}
