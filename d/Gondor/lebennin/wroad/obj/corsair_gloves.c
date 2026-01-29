/*
 * Black leather gloves - standard issue gloves for corsairs near Linhir
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
void
create_armour()
{
    set_name("gloves");
    set_short("black leather gloves");
    set_pshort("black leather gloveses");
    set_long("Made of black dyed leather, these tight fitting gloves affords " +
        "basic protection to their wearer.\n");
    set_default_armour(8, A_HANDS);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(8, A_HANDS));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
