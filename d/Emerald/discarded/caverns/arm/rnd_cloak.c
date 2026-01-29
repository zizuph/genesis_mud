inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_armour()
{
    set_name("cloak");
    set_adj("coarse");
    set_long("This "+short()+ " looks. like it belonged to a pirate.\n");
    set_ac(17);
    set_am( ({-2, 1, 1}) );
    set_at(A_ROBE);
}
