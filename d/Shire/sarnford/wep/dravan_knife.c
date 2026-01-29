/*
 * Knife for Billingsworth
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
    
    set_name(({"knife","fishing knife"}));
    set_pname(({"knives","fishing knives"}));
    set_short("short, jagged fishing knife");
    set_pshort("short, jagged fishing knives");
    set_adj(({"short", "jagged"}));
    set_long("This fishing knife has a short, jagged blade that looks like " +
        "it would really hurt if it hit someone.\n");
    	    
    rand = random(5);
    set_hit(17);
    set_pen(28);
    set_wt(W_KNIFE);
    set_dt(W_SLASH);
    set_hands(W_RIGHT);
    
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(22,22));
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    
}
