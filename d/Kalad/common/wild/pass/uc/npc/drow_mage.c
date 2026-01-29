inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
int heal;
void
create_monster()
{
   set_name("mage");
   add_name("wizard");
   set_race_name("drow");
   set_adj("treacherous");
   add_adj("conniving");
   set_short("drow mage");
   set_long("An utterly treacherous drow mage, his presence here, far "+
      "from the city of the drow only testifies to his power, for no "+
      "mediocre mage is ever present in the wilds of the underrealm, they "+
      "simply do not last that long.\n");
   set_extra_long("He has a large pouch hanging from his waist.\n");
   set_all_hitloc_unarmed(50); /* A permanent protective ac spell */
   set_stats(({100,180,140,150,125,100}));
   set_skill(SS_UNARM_COMBAT,15);
   set_skill(SS_WEP_KNIFE,60);
   set_skill(SS_DEFENCE,60);
   set_skill(SS_PARRY,30);
   set_skill(SS_AWARENESS,100);
   set_skill(SS_SPELLCRAFT,100);
   set_skill(SS_HIDE,50);
   set_skill(SS_SNEAK,50);
   set_alignment(-1000);
   set_knight_prestige(1000);
   set_act_time(3);
   add_act("smirk");
   add_act("grin menacingly all");
   add_act("cackle dem");
   add_act("laugh evil");
   add_act("hide");
   add_act("say Wael!");
   set_cact_time(3);
   add_cact("grin mer all");
   add_speak("The illithids are near, I can sense their presence.\n");
   set_default_answer("Iblith! Do not waste my time!\n");
   add_ask(({"illithids","illithid"}),
      "Their lair is somewhere nearby, I have yet to ascertain how many "+
      "of them there are, so that I might report back to Undraeth.\n");
   add_ask(({"undraeth"}),
      "It is the glorious city of all drow!\n");
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_SEE_DARK,10);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   trig_new("%w 'spits' %s","react_attack");
   trig_new("%w 'starts' 'to' 'search' %s","react_attack");
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
   arm = clone_object(CPASS(uc/arm/dm_robe));
   arm -> move(TO);
   arm = clone_object(CPASS(uc/arm/dm_belt));
   arm -> move(TO);
   command("wear all");
   wep = clone_object(CPASS(wep/dw_dagger));
   wep -> move(TO);
   command("wield all");
   MONEY_MAKE_GC(random(10))->move(TO,1);
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
      TO->command("emote gathers several items from a pouch on his belt.");
      TO->command("emote mumbles several arcane words.");
      TO->command("grin mer");
      set_alarm(3.0,0.0,"get_golem");
      return 0;
   }
   if(random(4))
      return 0;
   hitresult = enemy -> hit_me(400 + random(400), MAGIC_DT, me, -1);
   if (hitresult[0]>0)
      {
      me->catch_msg("You cast a magic missile spell at your enemy!\n");
      enemy->catch_msg(QCTNAME(me) + " mumbles several arcane words of magic "+
         "and then gestures in your direction.\n");
      tell_watcher(QCTNAME(me) + " mumbles several arcane words of magic "+
         "and then gestures in " + QTNAME(enemy) + "'s direction.\n", enemy);
      enemy->catch_msg("Several bolts of red energy pierce your body!\n");
      tell_watcher("Several bolts of red energy race from " + QTNAME(me) + "'s hands "+
         "and unerringly strike " + QTNAME(enemy) + "'s body.\n", enemy);
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
   me->catch_msg("You try to hit your enemy with a magic missile spell but miss!\n");
   enemy->catch_msg(QCTNAME(me) + " mumbles several arcane words of magic "+
      "and then gestures in your direction.\n");
   enemy->catch_msg("Several bolts of red energy fly from " + QTNAME(me) + "'s hands and nearly hit you!\n");
   tell_watcher(QCTNAME(me) + " mumbles several arcane words of magic and "+
      "then gestures in " + QTNAME(enemy) + "'s direction.\n", enemy);
   tell_watcher("Several bolts of red energy fly from " + QTNAME(me) + "'s hands "+
      "and nearly hit " + QTNAME(enemy) + "'s body.\n", enemy);
   return 0;
}
get_golem()
{
   object golem;
   golem = clone_object(CPASS(uc/npc/stone_golem))->move(E(TO));
   say("A stone golem arises from the ground!\n");
}
