/*
 * Old brandy flavoured tobacco, to smoke in the pipe
 */

inherit "/d/Shire/common/obj/tob_parent.c";
#include "/sys/stdproperties.h"

void
create_object()
{
    ::create_object();
    set_adj(({"old","brandy"}));
    set_short("Old Brandy tobacco");
    set_long(break_string(
	  "You are looking at good quality Old Brandy tobacco. "
	+ "You take a delightful sniff at it, and stare dreamily "
	+ "at the sky.\n", 70));

   add_prop(OBJ_I_VALUE, 14);
}

string
query_flavour()
{
    return "Old Brandy";
}
