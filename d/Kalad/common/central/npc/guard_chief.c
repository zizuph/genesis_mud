inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/money.h"

object wep;
/* by Korat */
create_monster()
{
   ::create_monster();
   set_name("arth");
   add_name("captain");
   set_race_name("human");
   set_adj("large");
   add_adj("stern");
   set_long("This man is the commanding officer of the plaza "+
      "guards. He has the responsibility to protect the surrounding "+
      "areas through using his men underneath his command. "+
      "But if the need arises, this man should be able to control "+
      "any situation by himself. A mighty fighter!\n");
   set_stats(({110,170,130,80,80,110}));
   set_alignment(500);
   set_skill(SS_WEP_POLEARM,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_PARRY,100);
   set_skill(SS_AWARENESS,70);
   set_skill(SS_BLIND_COMBAT,100);
   
   add_prop(NPC_M_NO_ACCEPT_GIVE,1); /* won't accept gifts */
      add_prop(CONT_I_WEIGHT, 80000);  /* weights 80 kilo's */
   add_prop(CONT_I_HEIGHT, 195);    /* 195 cm high */
   set_hp(query_max_hp()); /* heal fully */
   set_title("Captain of the Plaza guards");
   set_knight_prestige(-5);
   add_speak("Leave me alone! I have work to do.\n");
   
   set_act_time(2);
   add_act("emote polishes his military fork while staring thoughtfully "+
      "out of the window.");
   add_act("say What can I do for you?");
   add_act("hmm");
   set_cact_time(1);
   add_cact("say I can kill you with my bare hands!");
   add_cact("say Piss off will you? You have NO chance to win!");
   add_cact("say Leave or DIE!");
   trig_new("%w 'attacks' %s", "react_attack");
}

void
arm_me()
{
   object arm;
   seteuid(getuid(TO));
   arm = clone_object("/d/Kalad/common/central/arm/plghelm");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/central/arm/plggreav");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/central/arm/plggaunt");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/central/arm/plgplate");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/central/arm/plgrobe");
   arm -> move(TO);
   command("wear all");
   wep = clone_object("/d/Kalad/common/central/wep/fork");
   wep -> move(TO);
   MONEY_MAKE_GC(random(10))->move(TO,1);
}

int
react_attack(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(3.0,0.0,"return_attack",who);
      return 1;
   }
}
void
return_attack(string who){
   int ran;
   object obj;
   if(obj = present(who, environment())){
      command("say How dare you to attack me!");
      if(!wep->query_wielded())
         command("emote fetches a military fork from behind him with a superior glint in his eyes.");
      command("wield all");
      command("say Die then " + obj->query_nonmet_name() + "!");
      command("kill " + (obj->query_real_name()));
   }
}


int
special_attack(object enemy)
{
   object me;
   object wep;
   mixed* hitresult;
   string how;
   me = this_object();
   if(!wep->query_wielded())
      command("wield all");
   if(!wep->query_wielded())
      return 0;
   if (random(5))
      return 0;
   hitresult = enemy->hit_me(200 + random(500), W_BLUDGEON, me, -1);
   how = " scarcely";
   if (hitresult[0] > 0)
      how == "";
   if (hitresult[0] > 10)
      how = " quite";
   if (hitresult[0] > 20)
      how = " awfully";
   if (hitresult[0] > 30)
      how = " extremely";
   if (hitresult[0] > 40)
      how = " dreadfully";
   
   me -> catch_msg("You twist your military fork and thrusts it towards the enemy!\n" +
      capitalize(enemy->query_pronoun()) + " is"+ how + " hurt by "+
      "your military fork "+
      "when you twists it around and thrusts it in.\n");
   enemy -> catch_msg(QCTNAME(me) + " impales you with his military fork!\n" +
      "You feel" + how + " hurt.\n");
   tell_watcher(QCTNAME(me) + " impales " + QTNAME(enemy) + " with his fork!\n"+
      "The fork pierces "+enemy->query_objective() +
      ", hurting "+enemy->query_objective() + how + ".\n", enemy);
   if (enemy->query_hp() <= 0)
      enemy -> do_die(me);
   return 1;
}


tell_watcher(string str,object enemy)
{
   object me,*ob;
   int i;
   me = this_object();
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i=0;i<sizeof(ob);i++)
   if (ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
}
