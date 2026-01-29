/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/arm/guardhelm.c
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
  set_short("large sturdy helmet");
  set_long("This helmet is big and heavy.\n");
  set_adj("sturdy");
  add_adj("large");

  set_ac(15);
  set_am(({ 0, 0, 0}));
  set_at(A_HEAD);

  add_prop(OBJ_I_VALUE, 20);
  add_prop(OBJ_I_WEIGHT,4000);
  add_prop(OBJ_I_VOLUME,200);
}