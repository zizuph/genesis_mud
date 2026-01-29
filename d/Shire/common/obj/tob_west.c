/*
 * West flavoured tobacco, to smoke in the pipe
 */

inherit "/d/Shire/common/obj/tob_parent.c";
#include "/sys/stdproperties.h"

void
create_object()
{
    ::create_object();
    set_adj("west");
    set_short("west tobacco");
    set_long(break_string(
	  "This is the finest quality of tobacco from the West Farthing. "
	+ "You are looking forward to smoking it.\n", 70));

    add_prop(OBJ_I_VALUE, 1*12);
}

string
query_flavour()
{
    return "west";
}
