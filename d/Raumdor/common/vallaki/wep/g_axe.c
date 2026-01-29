inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/* Sarr */
/*     Modified:        Nerull, 17/10-09 (increased hit/pen to 34)*/

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
    set_hit(40);
    set_pen(40);
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_VALUE,900+random(200));
}
