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
    set_name("mace");
    add_name("club");
    set_adj("silver");
    add_adj("shiny");
    set_short("shiny silver mace");
    set_long("This mace is made of fine silver steel. It is big and "+
    "have shiny spikes. The haft is made of "+
    "heavy oak wood. This is indeed a powerful weapon.\n");
    set_dt(W_BLUDGEON);
    set_wt(W_CLUB);
    set_hit(40);
    set_pen(40);
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_VALUE,900+random(200));
}
