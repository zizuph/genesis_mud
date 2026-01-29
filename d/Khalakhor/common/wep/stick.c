/* File:          /d/Khalakhor/common/wep/stick.c
 * Creator:       Teth
 * Date:          April 13, 1997
 * Modifications:
 * Purpose:       This stick is cloned when a sign is broken.
 * Related Files: /d/Khalakhor/std/sign.c
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
    set_name("stick");
    add_name(({"weapon","club","wood"}));
    set_adj("rough");
    add_adj("wooden");
    add_pname(({"weapons","clubs"}));
    set_pname("sticks");
    set_short("rough stick");
    set_pshort("rough sticks");
    set_long("This is a rough stick, usable as a club. It appears to be " +
      "the broken remnants of a sign or display.\n");
    set_hit(4);
    set_pen(10);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);

    set_likely_break(20);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(4,10));
    add_prop(OBJ_I_WEIGHT,1200);
    add_prop(OBJ_I_VOLUME,1200);
}

