/*
 * An advanced helmet in the camp at the SE - SW road
 * Tapakah, 09/2021
 */

#pragma strict_types

#include "wa_types.h"
#include "ss_types.h"
#include "stdproperties.h"

#include "../defs.h"

#define HEROIC 138

inherit KSTDARMOUR;

mixed
wear ()
{
  object wearer = environment();
  if (! interactive(wearer))
    return 0;
  if (TP->query_base_stat(SS_DIS) < HEROIC)
    return "The emblem emits an icy wave over your fingers, and you "+
      "almost drop the helm, unable to wear it.\n";
  return 0;
}

void
lighten ()
{
  add_prop(OBJ_I_WEIGHT, query_prop(OBJ_I_WEIGHT)*2/3);
}

void
create_khalakhor_armour ()
{
  set_name("helm");
  add_name(({"helmet"}));
  add_adj("great");
  set_short("great helm");
  set_long("This great helm was crafted by the best smiths of Port Macdunn. "+
           "It covers the head really well, and the metal is very light. "+
           "It has an emblem protruding from its top, for being better " +
           "seen at the battlefield, so it likely belonged to a commander.\n");
  set_default_armour(40, A_HEAD|A_EARS, ({0,0,0}));
  set_af(TO);
  set_alarm(0.1, 0.0, lighten);
  add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));                             
  add_prop(MAGIC_AM_ID_INFO,
           ({"This helmet seems to require certain level of "+
             "authority to wear.\n", 50}));
  
  add_prop(OBJ_S_WIZINFO, "This helmet requires a DIS level of at least "+
           "138 (heroic) to be worn.\n");
}
