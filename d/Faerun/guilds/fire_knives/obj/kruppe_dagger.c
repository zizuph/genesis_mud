/*
 * Fine steel dagger for questnpc4.
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
    add_adj("steel");
    
    set_short("fine steel dagger");
    
    set_long("This dagger is made of fine high "
    +"quality steel. It is polished and well maintained, "
    +"but not particulary sharpened. You expect this "
    +"dagger has been used more for cutting fruit and "
    +"opening letters than actually fighting someone.\n");
    
    set_hit(15);
    set_pen(13);
    set_wt(W_KNIFE); 
    set_dt(W_SLASH | W_IMPALE); 

    add_prop(OBJ_I_WEIGHT,2500);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(15,13));

    set_hands(W_ANYH); 
}
