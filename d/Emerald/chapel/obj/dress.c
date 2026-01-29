inherit "/std/armour";

#include "../chapel.h"
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("dress");
    set_short("shimmering, white silk wedding dress");
    set_long(break_string("It is a shimmering, white silk wedding "+
       "dress that leaves little to the imagination.\n",76));
    set_adj("wedding");
    set_ac(0);
    set_am(({   0,     0,      0 }));
     set_at(A_ROBE);
    add_prop(OBJ_I_VALUE, 1728);
}

int
wedding_stuff()
{
    return 1;
}

mixed
wear_me()
{
    if (!this_player()->query_prop(IS_BRIDE))
	return break_string("You cannot wear the " + short() + " unless "+
	       "you are a bride!\n", 76);
    return ::wear_me();
}

int
for_bride()
{
    return 1;
}
