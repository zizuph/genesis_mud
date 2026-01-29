/*
 * Worn steel helmet - a standard issue helmet for corsairs near Linhir
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
void
create_armour()
{
    set_name("helmet");
    set_short("worn steel helmet");
    set_pshort("worn steel helmets");
    set_long("This battle-tested steel helmet has a simple construction. It " +
        "covers the entire face, with a guard for the nose and chin.\n");
    set_default_armour(18, A_HEAD);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(18));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(18, A_HEAD));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
