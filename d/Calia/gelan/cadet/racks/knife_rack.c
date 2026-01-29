
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
    set_adj("knife"); 
    add_adj("kni"); 
    set_short("knife rack"); 
    set_long("This is a rack for holding knives.\n"); 
}


int
fits(object ob)
{
    return (IS_WEAPON_OBJECT(ob) &&
            (ob->query_wt() == W_KNIFE) &&
            ::fits(ob)); 
}


int
value_object(object ob)
{
    return F_VALUE_WEAPON(ob->query_hit(), ob->query_pen()); 
}
