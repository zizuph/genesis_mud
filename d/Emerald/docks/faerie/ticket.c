inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name("ticket");
    add_name("the elf-emerald line");
    add_adj("brand");
    add_adj("new");
    set_long("The ticket looks like it is brand new. There "+
	     "are some symbols on it, of which you think you can make out "+
	     "an emerald and some elven cove.\n");
    add_prop(OBJ_I_VALUE, 18);
}

string
query_recover()
{
    return MASTER;
}
