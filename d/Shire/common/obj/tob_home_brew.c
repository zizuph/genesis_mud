/*
 * Home brew flavoured tobacco, to smoke in the pipe
 */

inherit "/d/Shire/common/obj/tob_parent.c";
#include "/sys/stdproperties.h"

void
create_object()
{
    ::create_object();
    set_adj(({"home","brew"}));
    set_short("home brew tobacco");
    set_long(break_string(
	  "This home brew tobacco does not smell good. It is clearly of "
	+ "the lowest quality you ever smelled. However, if you have not "
	+ "touched a pipe for a long time, this could do.\n", 70));

   add_prop(OBJ_I_VALUE, 7);
}

string
query_flavour()
{
    return "home brew";
}
