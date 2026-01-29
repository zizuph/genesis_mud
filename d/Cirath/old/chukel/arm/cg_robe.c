/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/arm/cg_robe.c
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
  set_short("guardian cloak");
  set_adj("guardian");
  add_adj("cirathian");
  set_long("This cloak is made of wool and is red and black with the sign "+
    "of the cirathian guardian force on it.\n");
  set_ac(12);
  set_am(({0,1,-1})); /* impale,slash,bludgeon */

  set_at(A_ROBE);
  add_prop(OBJ_I_VALUE, 50);
  add_prop(OBJ_I_WEIGHT,1500);
  add_prop(OBJ_I_VOLUME,1000);
}
