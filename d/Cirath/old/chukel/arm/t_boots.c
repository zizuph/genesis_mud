/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/arm/t_boots.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/armour";
inherit "/lib/keep";
#include "defs.h"
#include <wa_types.h>

void
create_armour()
{
    set_name("boots");
    set_adj("well-used");
    set_short("pair of well-used boots");
    set_pshort("pairs of well-used boots");

    set_long("These boots have appearently been used a lot. Apart from "+
      "that, they're also very dirty.\n");

    set_default_armour(7, A_FEET | A_LEGS, ({-1,1,0}), 0);

    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,1000);
}
