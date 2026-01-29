/*
 * Random item for the Scavanger hunt
 * Coded by Finwe September 2003
 * Originally coded for the Shire, cleaned up in October 2015
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    seteuid(getuid());
    set_name("horseshoe");
    set_adj("bent");
    set_short("bent horseshoe");
    set_long("This is "+short()+". It is in the shape of a bent 'U' " +
		"and hammered from iron. It is rusty from sitting out in the " +
		"rain, and bent and appears unusable. Along " +
		"the inside of the shoe, running round the center is a groove " +
		"with several square holes on either side of the shoe. Rumour " +
		"has it that if hung above the door, wth the ends pointing " +
		"upwards, those who live within are protected from bad luck.\n");

	add_prop(OBJ_I_WEIGHT, 1191);

	add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 400);
}
