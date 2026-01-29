/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/arm/t_helmet.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/armour";
inherit "/lib/keep";
#include "defs.h"
#include <wa_types.h>

void
create_armour()
{
  set_name("helmet");
  set_short("dirty helmet");
  set_long("The helmet is made of iron and has a thick layer of dirt on it. "+
           "It ought to be polished!\n");
  set_adj("dirty");

  set_ac(15);
  set_am(({ 0, 0, 0}));
  set_at(A_HEAD);

  add_prop(OBJ_I_VALUE, 40);
  add_prop(OBJ_I_WEIGHT,2000);
  add_prop(OBJ_I_VOLUME,1000);
}