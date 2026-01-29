/*
 * axe.c
 *
 * A simple axe for common-place use across the domain.
 *
 * Khail - May 13/97
 *
 * Updated to used the khalakhor std weapon
 *
 * Igneous Oct 27/98
 */
#pragma strict_types

#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define HIT  22
#define PEN  29

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
    set_name("axe");
    set_adj("single-bladed");
   set_short("battle axe");
   set_pshort("battle axes");
    add_adj("battle");
    set_long("This battle axe is designed one handed use, and " +
        "bears a single bearded blade on a haft about a foot and " +
        "a half long. The blade is forged from good steel, and " +
        "tightly fitted onto the oak handle.\n");

    set_wt(W_AXE);
    set_hands(W_ANYH);
    set_dt(W_SLASH);
    set_hit(HIT);
    set_pen(PEN);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}

