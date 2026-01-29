inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

create_object()
{
	set_short("T");
	set_long("t\n");
	set_name("t");

	add_prop(OBJ_S_SEARCH_FUN, "search_me");
}

search_me(object p, string s)
{
tell_room(environment(p), QCTNAME(p)+" searched `t` with "+s+".\n");
}
