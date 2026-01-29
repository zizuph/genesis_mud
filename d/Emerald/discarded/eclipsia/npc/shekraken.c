inherit "/std/monster";
inherit "/std/combat/unarmed";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Emerald/defs.h"

void
create_monster()
{
   set_race_name("kraken");
   add_name("behemoth");
   set_name("she-kraken");
   set_adj("terrible");
   set_gender(G_FEMALE);
   set_short("she-kraken");
   set_long("The great she-kraken probably doesn't get visitors very " +
      "often, though you can tell she enjoys company as you " +
      "glance around the room. Skulls and bones of various creatures " +
      "are strewn about the lair. This behemoth doesn't look " +
      "particularly friendly.\n");
   
   set_stats(({ 175, 75, 150, 75, 75, 175 }));
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
   
   set_attack_unarmed(1, 100, 40, W_BLUDGEON, 25, "nimble tentacle");
   set_attack_unarmed(2, 70, 100, W_BLUDGEON, 10, "huge tentacle");
   set_attack_unarmed(4, 80, 80, W_BLUDGEON, 25, "massive tentacle");
   set_attack_unarmed(8, 75, 50, W_BLUDGEON, 10, "gnarled tentacle");
   set_attack_unarmed(16, 100, 30, W_BLUDGEON, 10, "swift tentacle");
   set_attack_unarmed(32, 65, 60, W_BLUDGEON, 10, "really long tentacle");
   set_attack_unarmed(64, 35, 70, W_BLUDGEON, 10, "slimy tentacle");
   
   set_cact_time(2);
   add_cact("growl");
   set_cchat_time(4);
   add_chat("You dare to try and steal my treasure?!\n");
   add_chat("None shall pass. NONE SHALL PASS!\n");
   set_alarm(1.0, 0.0, "arm_me");
}


void
stop_player()
{
    tell_room(environment(), QCTNAME(this_player()) + " tries to pass, but is " +
        "stopped by the she-kraken.\n", ({ this_player(), this_object() }));
    this_player()->catch_msg("The she-kraken blocks your way.\n");
}

