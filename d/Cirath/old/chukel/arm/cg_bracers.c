/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/arm/cg_bracers.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/armour";
inherit "/lib/keep";
#include "defs.h"
#include <wa_types.h>

void
create_armour()
{
  set_name("bracers");
  set_short("pair of guardian bracers");
  set_pshort("pairs of guardian bracers");
  set_long("These bracers are made of steel and painted red and black, "+
    "the cirathian guard force's colours.\n");
  set_adj("guardian");
  add_adj("cirathian");

  set_ac(20);
  set_am(({ 0, 0, 0}));
  set_at(A_ARMS);
  
  add_prop(OBJ_I_VALUE, 75);
  add_prop(OBJ_I_WEIGHT, 3000);
  add_prop(OBJ_I_VOLUME, 1500);
}
