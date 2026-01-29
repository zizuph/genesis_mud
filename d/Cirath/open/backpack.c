
/*   An large backpack for the hardware store in Calia

    coder(s):   Maniac

    history:    
             1/6/96    made keepable                          Maniac
            25/3/96    inherit from new standard pack         Maniac
            31.1.94    Created                                Maniac
            2.2.95     Adapted to include standard backpack 
                       code                                   Maniac
    purpose:    hold items

    to do:      none
    bug:        none known
*/


#pragma save_binary

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep"; 

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "/d/Cirath/open/caliadomain.h"

object this;

void
create_wearable_pack()
{
    set_name("backpack");
    set_pname("backpacks");
    set_short("large backpack");
    set_pshort("large backpacks");
    set_adj("large");
    set_long("A large backpack ideal for the travelling warrior, " +
             "such as are common in Calia where it was made.  " +
             "It looks as though it can hold a lot of stuff.  " +
             "This item may be worn, and the `fill' and `empty' commands " +
             "may be used.\n");

    set_mass_storage(1); 

    set_keep(1); 

    add_prop(CONT_I_WEIGHT, 4500); 	/* grams */
    add_prop(CONT_I_MAX_WEIGHT, 150000); /* grams */
    add_prop(CONT_I_VOLUME, 8000); 	/* ml */
    add_prop(CONT_I_MAX_VOLUME, 150000); /* ml */

    add_prop(OBJ_I_VALUE, 450); 		/* Worth 450 cc */
 
    add_name("_calia_hardware_shop_");
    this = THIS;
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

