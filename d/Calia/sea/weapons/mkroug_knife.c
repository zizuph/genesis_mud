
/* 
    A knife wielded by the medium water krougs
    Originally coded by Maniac 13/9/96
    Changed for water krougs by Jaacar 2/12/97
*/ 

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit "/std/weapon"; 

void
create_weapon()
{
    set_name("stiletto"); 
    set_adj("sharp"); 
    set_short("sharp stiletto"); 
    set_long("This is a thin, narrow bladed knife that looks very sharp.\n");

    set_wt(W_KNIFE); 
    set_dt(W_SLASH | W_IMPALE); 
    set_hands(W_ANYH); 

    set_hit(16); 
    set_pen(16);  
}
