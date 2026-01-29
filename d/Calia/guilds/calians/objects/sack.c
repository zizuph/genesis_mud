
/*   An ordinary sack for the hardware store in Calia

    coder(s):   Maniac

    history:   31/5/96    made keepable                    Maniac
               25/3/96    changed to inherit from new standard    Maniac 
                5.6.95    bug removed                     Maniac
                20.4.94   bug removed                      Maniac 
                31.1.94    created                         Maniac
    purpose:    hold items

    to do:      none
    bug:        none known
*/


#pragma save_binary


inherit "/d/Genesis/std/pack";
inherit "/lib/keep"; 
#include <stdproperties.h>
#include "defs.h"
#include <macros.h>

void
create_pack()
{
    set_name("sack");
    set_pname("sacks");
    set_short("standard sack");
    set_pshort("standard sacks");
    set_adj("standard");
    set_long("An ordinary sack that looks as though it can " +
             "hold a reasonable amount of your stuff. The `fill' and " +
             "`empty' commands will work with this item.\n"); 

    set_mass_storage(1); 
     
    set_keep(1); 

    add_prop(CONT_I_WEIGHT, 1750); 	/* grams */
    add_prop(CONT_I_MAX_WEIGHT, 75000); /* grams */
    add_prop(CONT_I_VOLUME, 2000); 	/* ml */
    add_prop(CONT_I_MAX_VOLUME, 75000); /* ml */

    add_prop(OBJ_I_VALUE, 225); 		/* Worth 225 cc */
    add_name("_calia_hardware_shop_");
}


string
query_recover()
{
    return MASTER + ":" + query_container_recover() + query_keep_recover();
}


void
init_recover(string arg)
{
    init_container_recover(arg);
    init_keep_recover(arg); 
}

