inherit "/std/armour";
inherit "/lib/keep";
 
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>
 
void
create_armour()
{
    set_name("shield");
    set_adj(({"large","steel"}));
    set_short("large steel shield");
    set_pshort("large steel shields");
    set_long("This "+short()+" shield is large and protects " +
        "most of the body. It is round with the inscription of " +
        "a large star set in the center.\n");
    add_item(({"star", "inscription of a large star", "large star"}),
        "The star is engraved in the center of the shield. It " +
        "appears to be some sort of insgnia.\n");
    set_at(A_SHIELD);
    set_ac(35);
    set_am(({-2, -1, 3}));
    set_likely_break(3);
    set_likely_cond(20);
    set_keep(1);
 
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(25, A_SHIELD));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(35) + 100 + random(300));
}
