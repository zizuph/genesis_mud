/*
 * Dunlending weapon
 * Coded by Hordak@Genesis
 */

#pragma strict_types

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

void
create_weapon()
{
    seteuid(getuid());

    set_name("axe");
    set_short("fierce steel axe");
    set_long("This axe has a wooden handle wrapped with leather to " +
      "make the grip more comfortable. The blade is made of steel, " +
      "an alloy between iron and carbon. The axe looks rather " +
      "primitive, a weapon that has been created with small " +
      "resources. Nevertheless it is fierce looking " +
      "and quite a deadly weapon.\n");

    set_adj(({"fierce", "steel"}));

    set_hit(32);
    set_pen(36);

    set_wt(W_AXE);
    set_dt(W_SLASH);

    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(32, 36) + random(100));
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 1500);
}
