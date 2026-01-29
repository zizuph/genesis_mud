/*
 * An improved chainmail in the camp at the SE - SW road
 * Tapakah, 09/2021
 */

#pragma strict_types

#include "wa_types.h"
#include "stdproperties.h"
#include "../defs.h"

inherit KSTDARMOUR;

void
lighten ()
{
  add_prop(OBJ_I_WEIGHT, query_prop(OBJ_I_WEIGHT)*2/3);
}

void
create_khalakhor_armour ()
{
  set_name("chainmail");
  add_name(({"mail"}));
  add_adj(({"light", "steel"}));
  set_short("light steel chainmail");
  set_long("This chainmail, decorated with an engraving of a shamrock "+
           "is an excellent piece of craftsmanship. It's lighter than "+
           "you would expect, and sits well on your shoulders.\n");
  set_default_armour(37, A_BODY|A_ARMS, ({1,1,-2}));
  add_prop(OBJ_I_WEIGHT, query_prop(OBJ_I_WEIGHT)*67/100);
  set_alarm(0.1, 0.0, lighten);
}
