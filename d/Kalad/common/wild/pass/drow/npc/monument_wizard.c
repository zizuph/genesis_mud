inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/extra_long";

#include "/d/Kalad/defs.h"
/* by Antharanos */
int heal;
void
create_monster()
{
   set_name("mage");
   add_name("high mage");
   set_race_name("drow");
   set_adj("grim");
   add_adj("powerful");
   set_short("drow high mage");
   set_long("A very powerful drow mage, judging by the numerous runes "+
      "and sigils lining his face, a face that stares grimly back at you, as "+
      "if daring you to attack him.\n");
   set_extra_long("He has several pouches attached to his waist.\n");
   set_all_hitloc_unarmed(50); /* A permanent protective ac spell */
   set_stats(({110,110,130,25,25,100}));
   set_skill(SS_UNARM_COMBAT,15);
   set_skill(SS_WEP_KNIFE,60);
   set_skill(SS_DEFENCE,60);
   set_skill(SS_PARRY,30);
   set_skill(SS_AWARENESS,100);
   set_skill(SS_SPELLCRAFT,100);
   set_skill(SS_HIDE,50);
   set_skill(SS_SNEAK,50);
   set_alignment(-1100);
   set_knight_prestige(1100);
   set_act_time(3);
   add_act("smirk");
   add_act("grin menacingly all");
   add_act("cackle dem");
   add_act("laugh evil");
   add_act("hide");
   add_act("say Wael!");
   add_act("peer all");
   set_cact_time(3);
   add_cact("grin mer all");
   add_speak("I am the guardian of the monument, do not remain here, for your "+
      "presence offends me. Now be off, before I decide to make an example of you.\n");
   set_default_answer("Iblith! You ask too many questions!\n");
   add_ask(({"monument"}),
      "It is the monument to the founder of Undraeth, Lolth's first high "+
      "priestess, Undraya.\n");
   add_ask(({"undraya"}),
      "She is at the right hand of Lolth now, serving our queen's cause on "+
      "a greater plane of existence.\n");
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_SEE_DARK,10);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   trig_new("%w 'starts' 'to' 'search' %s","react_attack");
}
void
emote_hook(string emote, object actor, string ad)
{
    if(emote == "spit")
        set_alarm(3.0,0.0,&command("kill "+lower_case(actor->query_name())));
}

int
react_attack(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_attack",who);
      return 1;
   }
}
void
return_attack(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("say Iblith!");
      command("kill " + (obj->query_real_name()));
   }
}
void
arm_me()
{
   object wep, arm;
   seteuid(getuid(TO));
   arm = clone_object(CPASS(drow/arm/m_w_robe));
   arm -> move(TO);
   command("wear all");
   wep = clone_object(CPASS(wep/dw_dagger));
   wep -> move(TO);
   command("wield all");
   MONEY_MAKE_GC(random(15))->move(TO,1);
}
tell_watcher(string str, object enemy)
{
   object me, *ob;
   int i;
   me = TO;
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i=0;i<sizeof(ob);i++)
   if (ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
}

int
special_attack(object enemy)
{
   object me;
   mixed* hitresult;
   string how;
   int i;
   me = TO;
   if(random(20)==0)
      {
      TO->command("emote gathers several items from one of the pouches attached to his waist.");
      TO->command("emote mumbles several arcane words.");
      TO->command("grin men");
      set_alarm(3.0,0.0,"get_golem");
      return 0;
   }
   if(random(4))
      return 0;
   hitresult = enemy -> hit_me(450 + random(450), MAGIC_DT, me, -1);
   if (hitresult[0]>0)
      {
      me->catch_msg("You cast a lightning bolt at your enemy!\n");
      enemy->catch_msg(QCTNAME(me) + " mumbles several arcane words of magic "+
         "and then gestures in your direction.\n");
      tell_watcher(QCTNAME(me) + " mumbles several arcane words of magic "+
         "and then gestures in " + QTNAME(enemy) + "'s direction.\n", enemy);
      enemy->catch_msg("A lightning bolt strikes your chest!\n");
      tell_watcher("A lightning bolt flashes from " + QTNAME(me) + "'s hands "+
         "and strikes " + QTNAME(enemy) + " in the chest!\n", enemy);
      if (enemy->query_hp()<=0)
         {
         enemy->catch_msg("You feel your soul slipping away from your body...\n");
         tell_watcher(QCTNAME(enemy) + " collapses as " + enemy->query_possessive() + " soul is blasted from " + enemy->query_possessive() + " body by " + QTNAME(me) + "'s magic.\n", enemy);
         enemy->command("scream");
         enemy->command("shout Nooooooooooooo!!!");
         enemy->do_die(me);
       }
      return 0;
   }
   me->catch_msg("You try to hit your enemy with a lightning bolt spell but miss!\n");
   enemy->catch_msg(QCTNAME(me) + " mumbles several arcane words of magic "+
      "and then gestures in your direction.\n");
   enemy->catch_msg("A lightning bolt flashes towards you from " + QTNAME(me) + "'s hands and nearly hits you!\n");
   tell_watcher(QCTNAME(me) + " mumbles several arcane words of magic and "+
      "then gestures in " + QTNAME(enemy) + "'s direction.\n", enemy);
   tell_watcher("A lightning bolt flashes from " + QTNAME(me) + "'s hands "+
      "and nearly strikes " + QTNAME(enemy) + " with its terrible might.\n", enemy);
   return 0;
}
get_golem()
{
   object golem;
   golem = clone_object(CPASS(uc/npc/stone_golem))->move(E(TO));
   say("A stone golem arises from the ground!\n");
}
