
inherit "/std/weapon";
#include "/sys/wa_types.h"  

void
create_weapon()
{
    set_name("sword");
    set_short("shimmering sword"); 
    set_long("A beautiful blade made of shimmering steel, it has an unearthly quality...\n");
    set_adj("shimmering");
    set_hit(25);
    set_pen(30);

    set_wt(W_SWORD); 
    set_dt(W_SLASH | W_IMPALE); 

    set_hands(W_ANYH); 
}
