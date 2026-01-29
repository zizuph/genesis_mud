/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/arm/t_cloak.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/armour";
inherit "/lib/keep";
#include "defs.h"
#include <wa_types.h>

void
create_armour()
{
  set_name("cloak");
  set_short("filthy cloak");
  set_adj("filthy");
  set_long("This cloak is made of cotton and hasn't been washed the last century.\n");
  set_ac(6);
  set_am(({0,1,-1})); /* impale,slash,bludgeon */

  set_at(A_ROBE);
  
  add_prop(OBJ_I_VALUE, 3);
  add_prop(OBJ_I_WEIGHT,300);
  add_prop(OBJ_I_VOLUME,300);
}
