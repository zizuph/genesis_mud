
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
    set_adj("sword"); 
    add_adj("swo"); 
    set_short("sword rack"); 
    set_long("This is a rack for holding swords.\n"); 
}


int
fits(object ob)
{
    return (IS_WEAPON_OBJECT(ob) &&
            (ob->query_wt() == W_SWORD) &&
            ::fits(ob)); 
}


int
value_object(object ob)
{
    return F_VALUE_WEAPON(ob->query_hit(), ob->query_pen()); 
}
