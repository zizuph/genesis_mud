/*
 * Wooden spear.
 * Louie 2004
 */
 
inherit "/std/weapon";

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("spear");
    set_adj("wooden");
    add_name("polearm");
    set_short("wooden spear");
    set_long("This spear is long and thin, used for jabbing attacks "+
    	"that keep opponents at a distance.  The tip is elongated, with "+
    	"no barbs or ornamentation.  It is light enough "+
    	"for melee combat, but would be less useful against a larger "+
    	"foe or a mounted victim.  \n");
        
    set_hit(28);
    set_pen(25);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 8000);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(28, 25));
}

