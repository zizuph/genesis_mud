/*     Created by:      Sarr
 *     Location:        
 *     Modified:        Toby, 970919 (fixed typos and random hit/pen)
 *     Modified:        Nerull, 17/10-09 (increased hit/pen to 34)
 */
 /*     Modified:        Nerull, 2021, Updated with proper properties 
                        and hit/pen according to man weapon.      */

inherit "/std/weapon";
#include "/d/Raumdor/defs.h"


void
create_weapon()
{
    ::create_weapon();
    set_name("sword");
    add_name("longsword");
    set_adj("silver");
    add_adj("shiny");
    set_short("shiny silver longsword");
    set_long("This longsword is made of shiny silver like steel. It is "+
    "strong and sharp. You see a golden cross embedded in the cross "+
    "piece.\n");
    set_dt(W_IMPALE | W_SLASH);
    set_wt(W_SWORD);
    set_hit(35);
    set_pen(35);  
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35, 35) + random(20) -10);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(35, W_SWORD) +
        random(50) - 25);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
}
