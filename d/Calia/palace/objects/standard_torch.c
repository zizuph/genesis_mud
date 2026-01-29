/* A standard torch	

    coder(s):   Maniac

    history:    31.1.94          Created                      Maniac

    purpose:    provide light

    quests:     none
    special:    none

    to do:      
    bug:        none known
*/


#pragma save_binary

inherit "/std/torch";
#include "defs.h"
#include <stdproperties.h>

void
create_torch()
{
    set_name("torch");
    set_pname("torches");
    set_short("standard torch");
    set_pshort("standard torches");
    set_adj("standard");
    set_long("This is an ordinary looking torch.\n");

    set_time(240);
    set_strength(1);
  
    /* Taking price to be duration * strength / 2  */
    add_prop(OBJ_I_VALUE, 120);

    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 1500);

    add_name("_calia_hardware_shop_");

}

