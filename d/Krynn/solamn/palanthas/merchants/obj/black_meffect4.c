/*
 * Invisible object given to players who drink multiple
 * black meades at once.  It initiates the drunken
 * effects experienced by vict...  imbibers.
 *
 * Mortis 01.2006
 */

#include <language.h>
#include <macros.h>
#include "../../local.h"

inherit "/std/object";

object dri;

#include "black_meffects.h"

create_object()
{
	set_name("black_meade_effect1");
	add_name("test");
	set_short("I'm invisible");
	set_long("You can't see me!\n");

    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
	add_prop(OBJ_M_NO_SELL, 1);

	enable_commands();
	set_no_show(1);
	seteuid(getuid(this_object()));

	set_alarm(2.0, 0.0, "where_am_i");
	set_alarm(360.0, 0.0, "effect1");
	set_alarm(420.0, 0.0, "effect2");
	set_alarm(500.0, 0.0, "effect3");
	set_alarm(530.0, 0.0, "effect4");
	set_alarm(555.0, 0.0, "effect4");
	set_alarm(710.0, 0.0, "effect4");
	set_alarm(711.0, 0.0, "rem_me");
}

void
where_am_i()
{
	dri = E(TO);
}

void
rem_me()
{
	remove_object();
}
