 
inherit "/std/weapon";
 
#include "/sys/ss_types.h"
#include <stdproperties.h>
#include "/sys/wa_types.h"
 
void
create_weapon()
{
    set_name("axe");
    set_adj("steel");
    set_adj("sharpened");
    set_short("sharpened steel axe");
    set_long("Perfectly sharpened axe, made from steel of good "+
             "quality. It's a weapon of real warriors.\n"+
             "You don't want to see this axe in hands of "+
             "your enemy.\n");
 
 
    set_pen(30);
    set_hit(35);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);
 
}
