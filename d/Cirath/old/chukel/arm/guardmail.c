/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/arm/guardmail.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/armour";
inherit "/lib/keep";
#include "defs.h"
#include <wa_types.h>

void
create_armour()
{
  set_name("platemail");
  set_short("heavy guardian platemail");
  set_long("Ouch! This platemail is something else! Heavy.\n");
  set_adj("guardian");
  add_adj("heavy");

  set_ac(25);
  set_am(({-1,1,1}));
  set_at(A_TORSO);

  add_prop(OBJ_I_VALUE, 100);
  add_prop(OBJ_I_WEIGHT,13000);
  add_prop(OBJ_I_VOLUME,8000);
}
