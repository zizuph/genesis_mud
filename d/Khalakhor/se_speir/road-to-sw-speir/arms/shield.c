/*
 * A basic shield in the camp at the SE - SW road
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
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_VOLUME)*3/2);
}

void
create_khalakhor_armour ()
{
  set_name("shield");
  add_adj(({"elongated", "oval"}));
  set_short("elongated oval shield");
  set_long("This shield is shaped like an elongated oval. It is made "+
           "out of oak, and covered with tanned leather. It is very "+
           "light, but not particularly sturdy.\n");
  set_default_armour(25, A_SHIELD, ({3,0,-3}));
  set_alarm(0.1, 0.0, update_prop);
}
