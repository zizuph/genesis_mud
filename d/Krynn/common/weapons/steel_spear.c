/*
 * Steel spear.
 * Louie 2004
 */
 
inherit "/std/weapon";

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("spear");
    set_adj("steel");
    add_name("polearm");
    set_short("steel spear");
    set_long("This spear is shorter than most spears, but its shafter " +
    	"is thick and heavy.  " +
    	"The tip is short and quickly expands out, "+
    	"allowing the spear to inflict wide, gruesome wounds.  "+
    	"The butt of the spear is slightly weighted to provide "+
    	"enough balance to allow the spear to manipulated in one hand.  "+
    	"The spear is designed to be carried under the arm and used for "+
    	"lethal, puncturing thrusts.  \n");
        
    set_hit(25);
    set_pen(35);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 8000);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(25, 35));
}

