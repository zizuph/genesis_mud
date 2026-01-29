/*
 * Black breeches - standard issue breeches for corsairs near Linhir
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
void
create_armour()
{
    set_name("breeches");
    set_short("black breeches");
    set_pshort("black breecheses");
    set_long("Made of black leather, theese wide breeches ends at the knees.\n");

    set_default_armour(8, A_LEGS);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(12));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(8, A_LEGS));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
