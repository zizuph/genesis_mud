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
    set_short("large torch");
    set_pshort("large torches");
    set_adj("large");
     set_long("It is a rather large torch.\n");

     set_time(200);
    set_strength(1);
  
    /* Taking price to be duration * strength / 2  */
    add_prop(OBJ_I_VALUE, 100);

    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 1500);

}

