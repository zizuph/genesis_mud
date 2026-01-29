/*
 * A special sword in the camp at the SE - SW road
 * Tapakah, 09/2021
 */

#pragma strict_types

#include "wa_types.h"
#include "ss_types.h"
#include "stdproperties.h"

#include "../defs.h"

inherit KSTDWEAPON;


mixed
wield (object weapon)
{
  object wielder = environment();
  if (! interactive(wielder))
    return 0;
  if (! TP->is_khalakhor_blademaster() && TP->query_skill(SS_WEP_SWORD) < 100)
    return "The heron on the blade flares, the sword shakes in "+
      "your hand, and you lose your grip on it.\n";
  return 0;
}

void
create_khalakhor_weapon ()
{
  set_name("claymore");
  add_name(({"sword"}));
  add_adj(({"heron-marked"}));
  set_short("heron-marked claymore");
  set_long("This superb sword obviously belonged to a blademaster. "+
           "Perfectly balanced and wonderfully light, it bears the "+
           "mark of a heron on it's blade. Whoever managed to get it "+
           "from its original owner must have been a great fighter.\n");
  set_default_weapon(45, 45, W_SWORD, W_SLASH|W_IMPALE, W_BOTH);
  set_wf(TO);
  add_prop(OBJ_I_WEIGHT, 1800);
  add_prop(OBJ_I_VOLUME,  600);
  add_prop(OBJ_I_VALUE, query_prop(OBJ_I_VALUE) + 1000);
  add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
  add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));                             
  add_prop(MAGIC_AM_ID_INFO,
           ({"This claymore seems to be fit either only for the hands "+
             "of Blademasters, or for those who have reached the maximal "+
             "proficiency with the sword.\n", 50}));
  
  add_prop(OBJ_S_WIZINFO, "This claymore can only be wielded "+
           "by blademasters or those with sup. guru sword skill.\n");
}
