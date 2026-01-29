inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("breastplate");
    add_name("plate");
    set_ac(32);
    set_at(A_BODY);
    add_adj( ({ "flashy", "pretentious" }) );
    set_short("flashy pretentious breastplate");
    set_pshort("flashy pretentious breastplates");
    set_long("This armour is of fair quality, but it is terribly " +
             "gaudy. You can't understand how any sentient being " +
             "would want to be seen in this. It's of steel make, but " +
             "it is enamelled with gold...poorly. Mixed in with the " +
             "gold are brilliant purple and green dyed portions. " +
             "Truly ugly.\n");
    add_prop(OBJ_I_VOLUME, 3100);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(32, A_BODY));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(32));
}

