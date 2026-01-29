/*
 * Bree grown tobacco, to smoke in the pipe
 */

inherit "/d/Shire/common/obj/tob_parent.c";
#include "/sys/stdproperties.h"

void
create_object()
{
    ::create_object();
    set_adj("bree");
    set_short("bree tobacco");
    set_long(break_string(
	  "Not many people know it, but some villagers from Bree also grow "
	+ "tobacco. This is a piece of their finest.\n", 70));

    add_prop(OBJ_I_VALUE, 1*12);
}

string
query_flavour()
{
    return "Bree";
}
