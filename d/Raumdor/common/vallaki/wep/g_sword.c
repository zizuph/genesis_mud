/*     Created by:      Sarr
 *     Location:        
 *     Modified:        Toby, 970919 (fixed typos and random hit/pen)
 *     Modified:        Nerull, 17/10-09 (increased hit/pen to 34)
 */

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
    "piece. It is light weight and easy to handle.\n");
    set_dt(W_IMPALE | W_SLASH);
    set_wt(W_SWORD);
    set_hit(40);
    set_pen(40);
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_VALUE,900+random(200));
}
