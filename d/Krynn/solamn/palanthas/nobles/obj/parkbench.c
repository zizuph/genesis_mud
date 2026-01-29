/* stone.c: The thing that causes the tell effect.
   This is the gagged stone. */

#include <options.h>
#include <macros.h>
#include <composite.h>
#include "../../local.h";

inherit "/std/container";

create_container()
{
	set_name("bench");
	add_name("benches");
	set_short("series of curved marble benches");
	set_long("Three curved benches of translucent marble circle the pool "
	+ "on all but its east side.\n");

	add_prop(OBJ_I_NO_GET,1);
	enable_commands();
	setuid();
    seteuid(getuid());
 
}

void
remove_item(object ob)
{
    ob->remove_object();
}

/*
 * This object can't be paralyzed poisoned etc.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    set_alarm(0.0, 0.0, &remove_item(ob));
}
