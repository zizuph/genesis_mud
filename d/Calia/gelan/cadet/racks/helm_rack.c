
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
    set_adj("helm"); 
    add_adj("hel"); 
    set_short("helm rack"); 
    set_long("This is a rack for holding helms.\n"); 
}


int
fits(object ob)
{
    return (IS_ARMOUR_OBJECT(ob) &&
            (abs(ob->query_at()) & A_HEAD) &&
            ::fits(ob)); 
}


int
value_object(object ob)
{
    return F_VALUE_ARMOUR(ob->query_ac()); 
}
