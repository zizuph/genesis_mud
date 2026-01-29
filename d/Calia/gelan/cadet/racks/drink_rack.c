
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
    set_adj("drink"); 
    add_adj("dri"); 
    set_short("drink rack"); 
    set_long("This is a rack for holding drinks.\n"); 
}


int
fits(object ob)
{
    return (IS_DRINK_OBJECT(ob) &&
            ::fits(ob)); 
}
