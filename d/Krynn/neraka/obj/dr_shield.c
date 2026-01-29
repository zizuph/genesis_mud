inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("shield");
    set_default_armour(12, A_SHIELD, ({ 6, -2, -4 }));
    add_adj("small");
    set_short("small shield");
    set_long("It's a small shield but it would still protect you a little.\n");
    add_prop(OBJ_I_VOLUME, 550);
}
