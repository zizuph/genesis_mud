inherit "/std/monster";
inherit "/std/combat/unarmed";

#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "../edefs.h"

void
create_monster()
{
   set_race_name("kraken");
   add_name("dragon");
   set_gender(G_MALE);
   set_adj("vicious");
   set_short("kraken");
   set_long("The ancient beast is like nothing you've ever seen. " +
      "The enormous sea dragon has lived for ages on the flesh of " +
      "poor merfolk and many other foolhardy challengers who " +
      "have pranced into his lair in the past. A key is hanging " +
      "around the neck of the kraken.\n");
   
   set_stats(({ 150, 300, 150, 50, 50, 150 }));
   refresh_mobile();
   set_intoxicated(500);
   set_aggressive(1);
   
   add_prop(LIVE_I_QUICKNESS, 50);
   add_prop(LIVE_I_SEE_DARK, 5);
   add_prop(LIVE_I_SEE_INVIS, 1);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(NPC_I_NO_LOOKS, 1);
   add_prop(MAGIC_I_RES_COLD, 50);
   add_prop(MAGIC_I_RES_POISON, 90);
   add_prop(MAGIC_I_RES_WATER, 100);
   add_prop(MAGIC_I_RES_AIR, 50);
   add_prop(MAGIC_I_RES_MAGIC, 40);
   add_prop(MAGIC_I_BREATH_WATER, 1);
   
   set_skill(SS_DEFENCE, 100);
   set_skill(SS_BLIND_COMBAT, 100);
   set_skill(SS_AWARENESS, 100);
   set_skill(SS_UNARM_COMBAT, 100);
   
   set_hitloc_unarmed(1, 95, 98, "tentacle");
   set_hitloc_unarmed(2, 10, 2, "head");
   
   set_attack_unarmed(1, 100, 40, W_BLUDGEON, 50, "nimble tentacle");
   set_attack_unarmed(2, 70, 100, W_BLUDGEON,  10, "huge tentacle");
   set_attack_unarmed(4, 80, 80, W_BLUDGEON, 10, "massive tentacle");
   set_attack_unarmed(8, 75, 50, W_BLUDGEON, 10, "gnarled tentacle");
   set_attack_unarmed(16, 100, 30, W_BLUDGEON, 10, "swift tentacle");
   set_attack_unarmed(32, 65, 60, W_BLUDGEON, 5, "really long tentacle");
   set_attack_unarmed(64, 35, 70, W_BLUDGEON, 5, "slimy tentacle");
   
   set_cact_time(2);
   add_cact("grin");
   set_cchat_time(4);
   add_cchat("Lunch time already?\n");
   add_cchat("Oh, I see. You are the appetizer!\n");
   set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()
{
   object key;
   
   key = clone_object(ECLIPSIA_OBJ + "key");
   key->move(TO);
}
