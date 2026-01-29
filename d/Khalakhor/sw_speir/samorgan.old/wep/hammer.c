/* Hammer
 * for construction workers
 * Damaris 03/2001
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
    set_name("hammer");
    set_short("black steel hammer");
    set_pshort("black steel hammers");
    set_adj("steel");
    add_adj("black");
    set_long("The black steel hammer is well made, and bears the " +
      "mark of the village smith of SaMorgan on the handle.\n");
    add_item(({"handle", "grip", "hilt"}),
      "Bears the mark of Mica smith of SaMorgan.\n");

    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_CLUB);
    set_hands(W_BOTH);
    set_dt(W_BLUDGEON | W_IMPALE);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);

}
