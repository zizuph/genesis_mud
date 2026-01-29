/* File:          /d/Khalakhor/common/wep/splinter.c
 * Creator:       Teth
 * Date:          April 25, 1997
 * Modifications:
 * Purpose:       This splinter is cloned when a mooring
 *                supporting a pier is broken.
 * Related Files: /d/Khalakhor/ship/macdunn/under_pier.c
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/std/weapon";

#include <formulas.h>
#include <wa_types.h>

public void
create_khalakhor_weapon() 
{
    set_name("splinter");
    add_name(({"weapon","knife","wood","stick"}));
    set_adj("sleek");
    add_adj("wooden");
    add_pname(({"weapons","clubs","sticks"}));
    set_pname("splinters");
    set_short("sleek splinter");
    set_pshort("sleek splinters");
    set_long("This is a sleek splinter, usable as a knife. It appears " +
      "to be easily broken. It is a remnant of some sort of pole.\n");
    set_hit(6);
    set_pen(5);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);

    set_likely_break(20);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(6,5));
    add_prop(OBJ_I_WEIGHT,550);
    add_prop(OBJ_I_VOLUME,600);
}

