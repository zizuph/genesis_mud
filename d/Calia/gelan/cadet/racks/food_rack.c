
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
    set_adj("food"); 
    add_adj("foo"); 
    set_short("food rack"); 
    set_long("This is a rack for holding food.\n"); 
}


int
fits(object ob)
{
    return (IS_FOOD_OBJECT(ob) &&
            ::fits(ob)); 
}
