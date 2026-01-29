/*
 * South flavoured tobacco, to smoke in the pipe
 */

inherit "/d/Shire/common/obj/tob_parent.c";
#include "/sys/stdproperties.h"

void
create_object()
{
    ::create_object();
    set_adj("south");
    set_short("south tobacco");
    set_long(break_string(
	  "This is the finest quality of tobacco from the South Farthing. "
	+ "Slightly less than the tobacco that comes from the West Farthing, "
	+ "but still very pleasant to smoke.\n", 70));

    add_prop(OBJ_I_VALUE, 2*12);
}

string
query_flavour()
{
    return "south";
}
