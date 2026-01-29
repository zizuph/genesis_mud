/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/arm/cg_helm.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/armour";
inherit "/lib/keep";
#include "defs.h"
#include <wa_types.h>

void
create_armour()
{
  set_name("helm");
  set_short("guardian helm");
  set_long("This helmet is made of steel and are painted in red and black "+
           "colours. In the forehead, the sign of the cirathian guardian force "+
           "is placed.\n");
  set_adj("guardian");
  add_adj("cirathian");

  set_ac(18);
  set_am(({ 0, 0, 0}));
  set_at(A_HEAD);

  add_prop(OBJ_I_VALUE, 100);
  add_prop(OBJ_I_WEIGHT,3000);
  add_prop(OBJ_I_VOLUME,1500);
}
