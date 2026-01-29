/*
 * Light halberd designed for use in one hand.
 * Louie 2004
 */
 
inherit "/std/weapon";

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("halberd");
    set_adj("light");
    add_adj("wooden");
    add_name("polearm");
    set_short("light wooden halberd");
    set_long("This halberd has a long wooden shaft and a thin, "+
    	"light-weight head.  The blade tapers to a point, allowing  "+
    	"it to be used for slashing or impaling.  " +
    	"Its lightness allows the halberd to be used single-handedly, "+
    	"for quick, precise strikes.  \n");
        
    set_hit(31);
    set_pen(26);
    set_wt(W_POLEARM);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 10000);
    //Purposely make it a little more expensive since it's light.
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(31, 31));
}

