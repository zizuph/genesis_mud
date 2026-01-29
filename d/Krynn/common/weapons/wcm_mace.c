/*
 * Mace of the wandering Cleric of Morgion
 * by Teth, Feb 21, 1997
 */

inherit "/std/weapon";

#include <formulas.h>
#include <wa_types.h>
#include "/d/Krynn/common/defs.h"

public void
create_weapon() 
{
    set_name("mace");
    add_name(({"weapon","club"}));
    set_adj("knobbed");
    add_adj(({"iron","balled"}));
    add_pname(({"weapons","clubs"}));
    set_pname("maces");
    set_short("knobbed mace");
    set_pshort("knobbed maces");
    set_long("This knobbed mace is a favoured weapon of clerics. The long " +
       "wooden handle supports a spherical iron ball at one end, and " +
       "the iron globe itself is covered with rounded bumps.\n");
    set_hit(29);
    set_pen(20);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(29,20));
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,3000);
}


