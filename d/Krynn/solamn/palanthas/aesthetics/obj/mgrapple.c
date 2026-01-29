/*
 * Grapple sold at general eq store in Aesthetics
 * quarter of Palanthas.  Can be fastened to a rope
 * from the same store for climb enhancement.
 *
 * Mortis 05.2006
 *
 */

inherit "/std/object";
inherit "/lib/keep";

#include "../../local.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>

void
create_object()
{
    set_name("grapple");
	add_name("hook");
    set_adj("iron");
	add_adj("grappling");
	set_short("iron grapple");
    set_long("A small, iron grapple with four backward curving hooks that "
	+ "can be <fasten>ed to a rope for use in climbing.\n");

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE,  144);

    set_keep(1);
}

void
init()
{
	ADA("fasten");
}

int
fasten(string str)
{
	object *rope;
	string ropename;

	NF("Fasten?  Fasten what?  Your grapple to a rope?\n");
	if (!str)
		return 0;

	if (sscanf(str, "grapple to %s", ropename) != 1)
		return 0;

	NF("But you don't have any " + ropename + ".\n");
	if (!(rope = FIND_STR_IN_OBJECT(ropename, TP)) || !sizeof(rope))
		return 0;

	NF("You must release your rope before fastening a grapple to it.\n");
	if (rope[0]->query_held())
		return 0;

	if (rope[0]->add_grapple())
	{
		write("You fasten your iron grapple to your rope.\n");
		say(QCTNAME(TP) + " fastens an iron grapple to " + HIS(TP)
		+ " rope.\n");
		remove_object();
		return 1;
	}

	write("Your iron grapple cannot be fastened to that.\n");
	return 1;
}
