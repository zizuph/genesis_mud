/*
 * Wooden club coded by Lord Rastlin
 */

inherit "/std/weapon";

#include <formulas.h>
#include <wa_types.h>
#include "../local.h"

nomask
create_weapon() 
{
    set_name("stick");
    add_name(({"weapon","club"}));
    set_adj("wooden");
    add_pname(({"weapons","clubs"}));
    set_pname("sticks");
    set_short("wooden stick");
    set_pshort("wooden sticks");
    set_long("This is a wooden stick, that can be used as a club, if " +
	"you want to hit someone over the head.\n");
    set_hit(10);
    set_pen(12);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,12));
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,2700);
}
