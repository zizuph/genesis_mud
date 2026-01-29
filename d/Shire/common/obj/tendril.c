inherit "/std/object";

#include "defs.h"
#include "/sys/stdproperties.h"

void
create_object()
{
    set_name("tendril");
    set_adj(({"dragon's","dragon"}));
    set_short("dragon's tendril");
    set_long(break_string(
	  "The tendril has been cut of some dragon. You have heard "
	+ "stories of people turning dragon's tendrils into powerful "
	+ "spells.\n", 70));
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 8000);
}
