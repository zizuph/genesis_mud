/*
 * Northeast flavoured tobacco, to smoke in the pipe
 */

inherit "/d/Shire/common/obj/tob_parent.c";
#include "/sys/stdproperties.h"

void
create_object()
{
    ::create_object();
    set_adj("northeast");
    set_short("northeast tobacco");
    set_long(break_string(
	  "This is the finest quality of tobacco from the Northeast Farthing. "
	+ "The flavour of this tobacco is different because it is harvested "
	+ "from plants that grew on a chalk soil.\n", 70));

    add_prop(OBJ_I_VALUE, 3*12);
}

string
query_flavour()
{
    return "northeast";
}
