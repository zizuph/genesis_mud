/*
 * basket_sword.c
 *
 * A basket-hilted longsword for the guards in the village.
 * Khail - June 15/97
 */
#pragma strict_types

#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define HIT  27
#define PEN  24

inherit "/d/Khalakhor/std/weapon";

/*
 * Function name: create_khalakhor_weapon
 * Description  : Turns this object into a weapon.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_weapon()
{
    set_name("longsword");
   set_short("basket-hilted steel longsword");
   set_pshort("basket-hilted steel longswords");
    add_name("sword");
    set_adj("steel");
    add_adj("basket-hilted");
    set_long("The longsword is well made, and bears the " +
        "mark of the village guard of Port Macdunn on the " +
        "basket of wire mesh surrounding the grip.\n");

    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_SWORD);
    set_hands(W_RIGHT);
    set_dt(W_SLASH | W_IMPALE);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);

}
