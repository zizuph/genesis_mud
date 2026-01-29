#include "../guild.h"

inherit "/d/Emerald/common/guild/vamp/npc/trainer_base";


#include <ss_types.h>
#include <stdproperties.h>

void set_up_skills()
{
  create_skill_raise();

  sk_add_train(SS_ANI_HANDL, "control beasts", "animal handling",
      0, 60);
  sk_add_train(SS_HUNTING, "hunt", "hunting", 0, 90);
  sk_add_train(SS_CLIMB, "climb", "climb", 0, 70);
  sk_add_train(SS_ACROBAT, "perform acrobatic maneuvres",
      "acrobatics", 0, 70);
}

void 
create_trainer()
{
  set_name(({ "", "vampire_guild_trainer", "vampire_guild_trainer_1" }));
  set_race_name("elf");
  set_adj("tall");
  add_adj("lean");
  set_long("");
  set_stats(({ 200, 150, 200, 100, 100, 120 }));
  add_prop(NPC_I_NO_RUN_AWAY, 1);
  add_prop(LIVE_I_NEVERKNOWN, 1);
  refresh_mobile();
}
