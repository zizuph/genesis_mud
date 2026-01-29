inherit "/std/monster";

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "defs.h"

void
create_monster()
{
   set_name("prisoner");
   set_race_name("human");
   set_adj("big");
   set_adj("burly");
   set_short("big burly prisoner");
   set_long(
      "This prisoner is huge. He seems a bit unhappy about "+
      "his current situation. You wonder "+
      "where he got his machete. The guards "+
      "will be unhappy to know that their "+
      "'favorite' prisoner has gotten his hands "+
      "on a machete.\n"+
      "He is wearing broken shackles around his wrists.\n"+
      "He is chained to the floor by iron shackles.\n");
   set_stats(({90,87,90,78,81,95}));
   set_hp(TO->query_max_hp());
   set_skill(SS_WEP_KNIFE, 90);
   set_skill(SS_WEP_SWORD, 90);
   set_skill(SS_DEFENCE, 90);
   set_skill(SS_PARRY, 90);
   set_skill(SS_BLIND_COMBAT, 80);
   set_skill(SS_BLIND_COMBAT, 80);
   add_chat("Just wait till i get my hands on one of those guards!");
   add_chat("Now that i have this machete, all will die!");
   add_chat("Now that i have this machete, all will die!\n");
   seteuid(getuid(this_object()));
   set_alarm(1.0,0.0,"arm");
}


void
arm()
{
   object machete;
   machete = clone_object(CAVERNS_DIR+"arm/machete");
   machete->move(TO);
   command("wield all");
   command("wear all");
}




