/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/arm/guardrobe.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/armour";
inherit "/lib/keep";
#include "defs.h"
#include <wa_types.h>

void
create_armour()
{
  set_name("robe");
  set_short("guardian robe");
  set_adj("guardian");
  set_long("This robe is made of leather and has the sign of Cirath on it.\n");
  set_ac(5);
  set_am(({0,1,-1})); /* impale,slash,bludgeon */

  set_at(A_ROBE);
  add_prop(OBJ_I_VALUE, 10);
  add_prop(OBJ_I_WEIGHT,1000);
  add_prop(OBJ_I_VOLUME,500);
}
