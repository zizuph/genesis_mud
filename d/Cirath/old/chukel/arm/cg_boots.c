/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/arm/cg_boots.c
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
    set_adj("guardian");
    add_adj("cirathian");
    set_short("pair of guardian boots");
    set_pshort("pairs of guardian boots");

    set_long("These boots are of the kind that the cirathian guards use. "+
      "They are made of red and black leather, the coulours of the cirathian "+
      "guard force.\n");

    set_default_armour(15, A_FEET, ({-1,1,0}), 0);

    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_I_WEIGHT,3000);
    add_prop(OBJ_I_VOLUME,1500);
}
