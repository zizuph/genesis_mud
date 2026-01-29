/*
 * Heavy cutlass - a standard issue sword for corsairs near Linhir
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name(({"sword", "cutlass"}));
    set_short("heavy cutlasss");
    set_pshort("heavy cutlasses");
    set_long("A heavy steel cutlass crafted from quality steel. The short " +
        "heavy blade of the cutlass is slightly curved with a single edge. " +
        "The hilt features a basket-shaped guard.\n");
    add_item("blade", "The heavy blade is made from quality steel. The heavy " +
        "blade makes this an effective weapon in strong hands, able to deal " +
        "severe damage.\n");
    add_item("hilt", "The hilt is crafted from copper with a basked shaped " +
        "guard to defend the hands of the wielder. The handle is twined " +
        "with strong hemp string to increase the grip.\n");
    set_default_weapon(28, 35, W_SWORD, W_SLASH, W_ANYH);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35, W_SWORD));
    // Add to std weight
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(35, W_SWORD) * 2);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
