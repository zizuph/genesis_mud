inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("halberd");
    add_name("pike");
    set_adj("long");
    add_adj("steel");
    set_short("long steel pike");
    set_long("This long steel pike is quite heavy and is not overly impressive. " +
             "It is a mediocre weapon but still deadly in the hands of a strong " +
             "warriors.\n");
    set_default_weapon(40,40, W_POLEARM, W_IMPALE, W_BOTH);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 10000);
}
