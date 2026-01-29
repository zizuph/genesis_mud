/*
 * Orc sword - Sarn Ford
 * Varian - February 2015
 */

inherit "/std/weapon";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/bree/wep/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>


create_weapon()
{
    int rand;
    
    set_name(({"broadsword", "sword"}));
    set_pname(({"broadswords", "swords"}));
    set_short("deadly broadsword");
    set_pshort("deadly broadswords");
    set_adj(({"deadly"}));
    set_long("You are looking at a finely crafted, and quite deadly looking broadsword. " +
        "The blade appears to be nearly three feet long, with two fullers running a " +
        "quarter of the way up the blade. The sword is basket-hilted to help " +
        "guard your hand during combat.\n");
    	    
    rand = random(5);
    set_hit(18);
    set_pen(22);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_LEFT);
    
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(18,22));
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1100);
    
}
