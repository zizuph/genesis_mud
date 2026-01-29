inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/* Sarr */
/*     Modified:        Nerull, 17/10-09 (increased hit/pen to 34)*/
/*     Modified:        Nerull, 2021, Updated with proper properties 
                        and hit/pen according to man weapon.      */

void
create_weapon()
{
    ::create_weapon();
    set_name("axe");
    set_adj("war");
    add_adj("heavy");
    set_short("heavy war axe");
    set_long("This axe is made of fine silver steel. It is big and "+
    "double-edged. The blade is razor sharp, and the haft is made of "+
    "heavy oak wood. This is indeed a powerful weapon.\n");
    set_dt(W_SLASH);
    set_wt(W_AXE);
    set_hit(35);
    set_pen(35);  
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35, 35) + random(20) -10);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(35, W_AXE) +
        random(50) - 25);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
}
