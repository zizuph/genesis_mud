
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
    set_adj("polearm"); 
    add_adj("pol"); 
    set_short("polearm rack"); 
    set_long("This is a rack for holding polearms.\n"); 
}


int
fits(object ob)
{
    return (IS_WEAPON_OBJECT(ob) &&
            (ob->query_wt() == W_POLEARM) &&
            ::fits(ob)); 
}


int
value_object(object ob)
{
    return F_VALUE_WEAPON(ob->query_hit(), ob->query_pen()); 
}
