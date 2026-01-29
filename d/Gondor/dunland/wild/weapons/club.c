/*
 *
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


    set_name("mace");
    add_name("club");
    set_short("steel-headed warhammer");
    set_long("This has a wooden handle with a head made of steel, " +
      "an alloy between iron and carbon. The head of the axe " +
      "is two half-spheres of steel attached to a wooden square " +
      "atop of a wooden pole. It is clearly a warhammer that has " +
      "been made with small resources, but it feels well balanced " +
      "and obviously, you can deal out some deadly damage with " +
      "it.\n");

    set_adj(({"steel-headed", "steel"}));

    set_hit(31);
    set_pen(35);

    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);

    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(31, 35) + random(100));
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2000);
}
