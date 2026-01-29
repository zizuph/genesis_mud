
/* 
   A gutting knife wielded by Mar-Iella in the coastal village.  

   Coded by Maniac 13/9/96
*/ 

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit "/std/weapon"; 

void
create_weapon()
{
    set_name("knife"); 
    set_adj("gutting"); 
    set_short("gutting knife"); 
    set_long("A sharp knife used for gutting fish.\n"); 

    set_wt(W_KNIFE); 
    set_dt(W_SLASH | W_IMPALE); 
    set_hands(W_ANYH); 

    set_hit(14); 
    set_pen(14);  
}

