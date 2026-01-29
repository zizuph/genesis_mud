/*
 * A basic leggings in the camp at the SE - SW road
 * Tapakah, 09/2021
 */

#pragma strict_types

#include "wa_types.h"
#include "stdproperties.h"

#include "../defs.h"

inherit KSTDARMOUR;

void
update_prop ()
{
  add_prop(OBJ_I_WEIGHT, query_prop(OBJ_I_WEIGHT)*3/4);
}

void
create_khalakhor_armour ()
{
  set_name("leggings");
  set_pname("leggings");
  add_adj(({"studded", "leather"}));
  set_short("studded leather leggings");
  set_long("These leggings are made out of thick hide. They are studded "+
           "with metal pieces, likely steel, and provide a decent extra "+
           "defense for the legs while being quite light.\n");
  set_default_armour(20, A_LEGS, ({-3,3,0}));
  set_alarm(0.1, 0.0, update_prop);
  
}
