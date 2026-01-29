/* Jaryx, bouncer at the Golden Inix Inn, Tyr */

inherit "/d/Cirath/std/monster.c";
#include "defs.h"
#include <wa_types.h>


object me=this_object();
void
create_monster()
{
  ::create_monster();
  set_name("jaryx");
  set_adj("easy-going");
  set_adj("calm");
  set_title("the doorman of the Golden Inix Inn");
  set_race_name("half-giant");

  set_long("This large half-giant seems "+
    "rather relaxed, almost nonchalant.  However, "+
    "his friendly demeanor is belied by his nasty looking "+
    "weapon, and apparent willingness to use it, should "+
    "trouble arise.\n");

  add_prop(NPC_I_NO_RUN_AWAY,1);

  set_stats(({210, 110, 130, 40, 70, 100}));
  set_skill(SS_DEFENCE, 75);
  set_skill(SS_PARRY, 65);
  set_skill(SS_WEP_CLUB, 75);
  set_skill(SS_UNARM_COMBAT, 40);

  set_alignment((random(1200)-600));

  add_act("emote leans against the bar.");
  add_act("emote smiles confidently.");
  add_act("emote watches you closely.");
  add_act("emote eyes you appraisingly.");
  add_act("emote relaxes beside the door.");
  add_act("say Welcome.");

  add_cact("emote does not look very friendly now.");
  add_cact("emote swings his weapon as if it's weightless.");
  add_cact("say Want no trouble here.");
  set_act_time(6);
  set_cact_time(3);

  set_default_answer(QCTNAME(me)+ " replies: I just guard. "+
    "I don't know.\n");
  set_speak("This job good money. Get to hit people!");
}

void
arm_me()
{
  clone_object(ATH_WEAPON+"h_mstar.c")->move(TO);
  clone_object(ATH_ARMOUR+"l_shirt.c")->move(TO);
  clone_object(ATH_ARMOUR+"l_bracers.c")->move(TO);
  command("wield all");
  command("wear all");
}

int
special_attack(object enemy)
{
 object me;
 mixed* hitresult;
 string how;

 me=this_object();

 if(random(5)) return 0;

 hitresult=enemy->hit_me(300+random(300),W_BLUDGEON, me, -1);
 how="amazed by such a feeble attack";
 if (hitresult[0] > 0) how = "dazed";
 if (hitresult[0] > 15) how= "injured";
 if (hitresult[0] > 30) how= "hurt";
 if (hitresult[0] > 50) how= "severely hurt";
 if (hitresult[0] > 75) how= "on the verge of collapse";

 enemy->catch_msg(QCTNAME(me) + " headbutts you viciously!\n");
 enemy->catch_msg("You feel "+ how + ".\n");

 tell_watcher(QCTNAME(me) + " headbutts " + QCTNAME(enemy)+
   " viciously!\n",me,enemy);

 if(enemy->query_hp() <= 0) enemy->do_die(me);

 return 1;
}
