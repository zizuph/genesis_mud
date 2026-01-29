inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("helmet");
    set_default_armour(9, A_HEAD, ({ -5, 0, 5 }));
    add_adj( ({ "small", "black" }) );
    set_short("small black helmet");
    set_long("It's a small black helmet, popular among the draconians.\n");
    add_prop(OBJ_I_VOLUME, 150);
}

