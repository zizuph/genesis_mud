inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
inherit "/d/Kalad/lib/extra_long";

#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("malaggar");
   add_name("patron");
   add_name("weaponmaster");
   add_name("master");
   set_race_name("drow");
   set_adj("large");
   add_adj("brutish");
   set_long("An unusually large drow male, though already showing signs "+
      "of middle age, his body appears trim and quite fit. The true indication "+
      "of his prowess is the burning stare from his eyes, a warning to those "+
      "that would underestimate him.\n");
   set_extra_long("From the symbol of a black widow spider perched atop "+
      "two crossed halberds, it appears as if he belongs to House Noquar.\n");
   set_stats(({120,150,120,25,25,100}));
   set_alignment(-1000);
   set_skill(SS_WEP_POLEARM,99);
   set_skill(SS_DEFENCE,75);
   set_skill(SS_PARRY,75);
   set_skill(SS_AWARENESS,75);
   set_skill(SS_BLIND_COMBAT,90);
   set_skill(SS_HIDE,50);
   set_skill(SS_SNEAK,50);
   set_act_time(6);
   add_act("emote gazes at you with fiery red eyes.");
   add_act("say Oloth zhah tuth abbil lueth ogglin.");
   add_act("say Sarn.");
   add_act("say Quarvalsharess zhah ultrin!");
   set_cact_time(3);
   add_cact("say Quarvalsharess plynn dos!");
   add_cact("say Elghinn ulu dos!");
   add_cact("shout Noquar ultrin!");
   add_cact("shout Noquar ulu usstan!");
   set_knight_prestige(1000);
   add_speak("How dare you speak to me, cur!\n");
   set_title("Noquar, the Patron and Weaponmaster of House Noquar");
   add_prop(LIVE_I_SEE_DARK,10);
   add_prop(NPC_I_NO_RUN_AWAY,1);
}
void
emote_hook(string emote, object actor, string ad)
{
    if(emote == "spit")
        set_alarm(2.0,0.0,"return_attack",actor);
}

void
return_attack(object obj)
{
   if(present(obj, environment()))
      {
      command("say Elghinn plynn dos, iblith!");
      command("kill " + (obj->query_real_name()));
   }
}

void
arm_me()
{
   object wep, arm;
   seteuid(getuid(TO));
   arm = clone_object("/d/Kalad/common/wild/pass/arm/dw_helm");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/wild/pass/arm/dw_chain");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/wild/pass/arm/piwafwi");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/wild/pass/arm/dw_boots");
   arm -> move(TO);
   command("wear all");
   arm = clone_object(CPASS(drow/obj/h8_insignia));
   arm -> move(TO);
   wep = clone_object(CPASS(drow/wep/h8_pat_halberd));
   wep -> move(TO);
   command("wield all");
   MONEY_MAKE_GC(random(12))->move(TO,1);
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("say Wael! Elghinn plynn dos!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
int
special_attack(object enemy)
{
   object me;
   mixed *hitresult;
   string how;
   me = TO;
   if(random(15))
      return 0;
   hitresult = enemy->hit_me(300 + random(300), W_BLUDGEON, me, -1);
   how = " with little success";
   if(hitresult[0] > 0)
      how == "";
   if(hitresult[0] > 5)
      how = " bruisingly";
   if(hitresult[0] > 10)
      how = " painfully";
   if(hitresult[0] > 15)
      how = " very painfully";
   if(hitresult[0] > 20)
      how = " painfully hard";
   if(hitresult[0] > 25)
      how = " incredibly hard";
   if(hitresult[0] > 30)
      how = " with devastating effectiveness";
   if(hitresult[0] > 35)
      how = " with a fatal blow";
   me -> catch_msg("You attempt to impale your opponent!\n"+
      capitalize(enemy->query_pronoun()) + " is hit"+
      how + ".\n");
   enemy -> catch_msg(QCTNAME(me) + " attempts to impale you with his weapon!\n"+
      "You are hit" + how + ".\n");
   tell_watcher(QCTNAME(me) + " attempts to impale " + QTNAME(enemy) + " with his weapon!\n"+
      capitalize(enemy->query_pronoun()) + " is hit" +
      how + ".\n", enemy);
   if(enemy->query_hp() <= 0)
      enemy->do_die(me);
   return 1;
}