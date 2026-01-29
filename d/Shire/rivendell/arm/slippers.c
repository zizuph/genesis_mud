inherit "/std/armour";
inherit "/lib/keep";
 
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <language.h>
 
void
create_armour()
{
    set_name("slippers");
    set_adj(({"light","woven"}));
    set_short("pair of light woven slippers");
    set_pshort("pairs of light woven slippers");
    set_long("This "+short()+" appear to be woven of some " +
        "elven fabric. You can't tell what the fabric is but " +
        "they are strong and sturdy yet comfortable to wear.\n");
 
    set_at(A_FEET);
    set_ac(12);
    set_am(({-2, -3, 5}));
    set_keep(1);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(12, A_FEET));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(12) + random(25));
}
