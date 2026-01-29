/* This is a old gnome Jessup's coat.
Created by Bishop of Calia 6/11/98 */

inherit "/std/armour";

#include <wa_types.h>       
#include <formulas.h>      
#include <stdproperties.h>  
#include <macros.h>
#include "defs.h"

#define ARMOUR_CLASS 4

void
create_armour()
{
    set_name("coat");

    set_adj("crimson");
    set_adj("brocaded");

    set_short("crimson brocaded coat");
    set_pshort("crimson coats");

    set_long("The exquisite fabric used in this coat is soft to" +
        " the touch. It has been dyed a sharp crimson colour, with" +
        " silver buttons. The sleeves are pure white, and slightly" +
        " puffed up.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);
    set_am(({ -1,2,-1 }));

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 4000);
}