/* trainer.c: Gladiator trainer: Shiva, ?. */

inherit "/std/monster";
inherit "/d/Emerald/common/guild/vamp/npc/shiva_train";

#include <stdproperties.h>
#include <ss_types.h>
#include "guild.h"

void set_up_skills()
{
  create_skill_raise();

  sk_add_train(SS_ANI_HANDL, "control beasts", "animal handling",
      0, 60);
  sk_add_train(SS_HUNTING, "hunt", "hunting", 0, 80);
  sk_add_train(SS_CLIMB, "climb", "climb", 0, 70);
  sk_add_train(SS_TRADING, "make deals", "trading", 0, 70);
  sk_add_train(SS_ACROBAT, "perform acrobatic maneuvres",
      "acrobatics", 0, 70);
  sk_add_train(SS_AWARENESS, "perceive", "awareness", 0, 100);
  sk_add_train(SS_SNEAK, "sneak", "sneak", 0, 80);
  sk_add_train(SS_HIDE, "hide", "hide", 0, 80);
  sk_add_train(SS_BLIND_COMBAT, "fight while blind",
      "blindfighting", 0, 70);
  sk_add_train(SS_APPR_MON, "appraise enemies", "appraise enemy", 0, 70);
  sk_add_train(SS_UNARM_COMBAT, "fight unarmed", "unarmed combat",
      0, 90);
  sk_add_train(SS_DEFENCE, "defend yourself", "defence", 0, 90);
}

void 
create_monster()
{
  set_name(({ "Bobo", "trainer" }));
  set_title("the vampire dude");
  set_living_name("_Bobo_");
  set_race_name("human");
  set_adj("tall");
  add_adj("lean");
  set_long("Just a trainer.\n");
  set_stats(({ 200, 150, 200, 100, 100, 120 }));
  add_prop(NPC_I_NO_RUN_AWAY, 1);
  add_prop(LIVE_I_NEVERKNOWN, 1);
  refresh_mobile();

  set_up_skills();
}

public int query_init_master() { return 1; }

init_living()
{
  ::init_living();
  init_skill_raise();
}

int query_skill(int skill)
{
  return (skill < 25 ? 100 : ::query_skill(skill)); 
}

int sk_no_train(object who)
{
  if (!IS_MEMBER(who) && !EMRLD_WIZ(who))
  {
    command("say Only true vampires may train here!");
    return 1;
  }

/*
  if (CHECK_PUNISHMENT(BAR, TP->query_real_name()))
  {
    command("say Sorry " + TP->query_name() + ", but you are " +
        "considered unworthy to train here.");
    return 1;
  }
*/

  return 0;
}
