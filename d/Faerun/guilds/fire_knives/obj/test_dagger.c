/*
 * Fine test dagger. Only for test purposes.
 *
 * Nerull 2019 
 */
#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit FAERUN_WEP_BASE;

void
create_faerun_weapon()
{

    set_name("dagger");
    
    set_adj("fine");
    add_adj("test");
    
    set_short("fine test dagger");
    
    set_long("This dagger is made of fine high "
    +"quality steel. It is polished and well maintained, "
    +"balanced and sharpened. This dagger is for testing purposes "
    +"only.\n");
    
    set_hit(40);
    set_pen(40);
    set_wt(W_KNIFE); 
    set_dt(W_SLASH | W_IMPALE); 

    add_prop(OBJ_I_WEIGHT,2500);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(15,13));

    set_hands(W_ANYH); 
}


int set_dull(int du)
{
	return 0;
}