/* A quality torch	

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
    set_short("quality torch");
    set_pshort("quality torches");
    set_adj("quality");
    set_long("This is a torch that seems to be well made, " +
             "to burn both brightly and for a long duration." +
             "\n");

    set_time(600);
    set_strength(2);
  
    /* Taking price to be duration * strength / 2  */
    add_prop(OBJ_I_VALUE, 600);

    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2000);

    add_name("_calia_hardware_shop_");

}