/* File         : /d/Terel/silver_new/weapon/spear.c
 * Creator      : Udana	
 * Date         : March 2006         
 * Purpose      : Rommenus Spear
 * Related Files: 
 * Comments     : 
 * Modifications: Modified by Pasqua
 */

inherit "/std/weapon";

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("spear");
    add_name("polearm");
    
    set_adj("blackened");
    add_adj("wooden");
    set_short("blackened spear");
    set_long("The shaft of this spear is about 2 metres long and made of "+
             "blackened wood. Spears like this one are best to be used "+
             "from horseback, but experienced fighter could make a good use "+
             "of it standing on his feet.\n");

    set_hit(32);
    set_pen(37);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 12000);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(32, 37));
}