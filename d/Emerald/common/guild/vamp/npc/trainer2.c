#include "../guild.h"

inherit "/d/Emerald/common/guild/vamp/npc/trainer_base";

#include <ss_types.h>
#include <stdproperties.h>

void set_up_skills()
{
  create_skill_raise();

  sk_add_train(SS_TRADING, "make deals", "trading", 0, 70);
  sk_add_train(SS_AWARENESS, "perceive", "awareness", 0, 100);
  sk_add_train(SS_SNEAK, "sneak", "sneak", 0, 80);
  sk_add_train(SS_HIDE, "hide", "hide", 0, 80);
  sk_add_train(SS_LANGUAGE, "speak foreign and archaic languages",
      "language", 0, 75);
  sk_add_train(SS_CLIMB, "climb", "climb", 0, 40);
  sk_add_train(SS_LOC_SENSE, "avoid getting lost", "location sense", 0, 60);
  sk_add_train(SS_DEFENSE, "dodge attacks", "defense", 0, 30);
  sk_add_train(SS_UNARM_COMBAT, "fight while unarmed", "unarmed combat", 
      0, 20);
}

void 
create_trainer()
{
  set_name(({ "", "vampire_guild_trainer", "vampire_guild_trainer_2" }));
  set_race_name("elf");
  set_adj("tall");
  add_adj("lean");
  set_long("");
  set_stats(({ 200, 150, 200, 100, 100, 120 }));
  add_prop(NPC_I_NO_RUN_AWAY, 1);
  add_prop(LIVE_I_NEVERKNOWN, 1);
  refresh_mobile();
}

