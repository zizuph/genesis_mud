/*
 * Boarding axe - a standard issue axe for corsairs near Linhir
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("axe");
    set_short("boarding axe");
    set_pshort("boarding axes");
    set_long("A long steel oak-handled axe with a chisel-shaped blade.\n");
    add_item("blade", "The chisel-shaped head of the axe has slightly " +
        "curved cutting edge and a sharp spike end.\n");
    add_item("handle", "The oak handle is about two feet long. The handle " +
        "is tapered down sharply towards the axe head, swelling in " +
        "diameter for the top hand and tapering down to the ball shaped " +
        "end.\n");
    set_default_weapon(28, 35, W_AXE, W_SLASH, W_ANYH);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35, W_AXE));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(35, W_AXE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
