/* A magical dragonscale armour */

inherit "/d/Krynn/common/obj/dragonarmour";

#include <wa_types.h>

void
create_dragon_armour()
{
    set_color("dark night-blue");
    add_adj(({ "dark", "night-blue" }));
    set_long("It is a body armour made from @@query_color@@ dragon scales, " +
             "trimmed in gold. It must be especially protective. You can " +
             "feel a strange power radiating from the armour and you " +
	     "@@query_feeling_about_armour@@. Golden ornaments decorate " +
             "this armour.\n");
    set_at(A_BODY);
}
