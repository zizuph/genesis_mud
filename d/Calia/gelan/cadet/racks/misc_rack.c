
/*
 *   A rack for the cadets. Coded by Maniac, 7/3/99
 */ 

#include "defs.h"
#include <files.h>
#include <formulas.h>
#include <wa_types.h>

inherit GC_RACK; 


void
create_rack()
{
    set_adj("miscellaneous"); 
    add_adj("mis"); 
    add_adj("misc"); 
    set_short("miscellaneous rack"); 
    set_long("This is a rack for holding miscellaneous items.\n"); 
}


int
fits(object ob)
{
    int t; 
    return (::fits(ob) &&  
            !IS_TORCH_OBJECT(ob) && 
            !IS_RECEPTACLE_OBJECT(ob) && 
            !IS_FOOD_OBJECT(ob) && 
            !IS_DRINK_OBJECT(ob) && 
            !(IS_WEAPON_OBJECT(ob) && ((t = ob->query_wt()) == W_SWORD ||  
                                       t == W_POLEARM ||
                                       t == W_AXE ||  
                                       t == W_KNIFE || 
                                       t == W_CLUB)) && 
            !(IS_ARMOUR_OBJECT(ob) && ((t = abs(ob->query_at())) == A_SHIELD || 
                                       (t & A_ROBE) || 
                                       (t & A_LEGS) ||  
                                       (t & A_ARMS) || 
                                       (t & A_HEAD) || 
                                       (t & A_BODY))));  
} 

