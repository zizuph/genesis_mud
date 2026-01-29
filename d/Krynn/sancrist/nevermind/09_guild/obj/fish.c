/* Created by Dajala
 * Falls from the tap.
 */

inherit "/std/object";

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

int alarm;

void
create_object()
{
	set_name("fish");
	add_name("tap_fish");
	set_pname("fishes");
	set_adj("smelly");
	add_adj("brown");
	set_short("smelly, brown fish");
	set_long("The fish flaps desperately. The poor animal will "
		+ "probably die soon.\n");
	add_prop(OBJ_I_WEIGHT, 1000);
	add_prop(OBJ_I_VOLUME, 500);
	add_prop(OBJ_M_NO_GET, "You try grab the fish but it flaps wildly "
		+ "and so you lose it again.\n");
	add_prop(OBJ_I_VALUE, 100);
	set_alarm(50.0, -1.0, "fish_dies");
}

void
fish_dies()
{
	tell_room(E(TO), "The fish's flapping ceases. It died.\n");
	set_short("dead, smelly, brown fish");
	add_adj("dead");
	set_long("Now you realize why it smells like dead fish "
		+ "here. This fish is very dead.\n");
	remove_prop(OBJ_M_NO_GET);
	remove_prop(OBJ_I_VALUE);
	alarm = set_alarm(50.0, 50.0, "stinking_fish");
	set_alarm(200.0, -1.0, "remove_fish", 0);
}

void
stinking_fish()
{
	object where;

	if(living(E(TO)))
		where = E(E(TO));
	else
		where = E(TO);
	tell_room(where, "A terrible smell like dead fish "
		+ "pervades the environment.\n");
}

void
remove_fish(int flag)
{
	if(living(E(TO)))
		write("The dead fish decays rapidly.\n");
	else 
		tell_room(E(TO), "A gnome comes in and smells "
			+ "around. He then grabs the stinking fish, "
			+ "growls at you and leaves again.\n");
	remove_alarm(alarm);
	remove_object();
}
