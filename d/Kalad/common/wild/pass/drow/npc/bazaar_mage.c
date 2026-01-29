inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define HAVE_BEEN_CHANGED "_have_been_changed"
/* This is the drow mage in the Undraeth bazaar where one may get 
their sex changed */
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("alak");
   add_name("mage");
   set_race_name("drow");
   set_adj("thin");
   add_adj("feeble");
   set_short("drow mage");
   set_long("A tall and almost unnaturally thin drow male, apparently in "+
      "his middle years, which would place him around three or four centuries "+
      "in age. His white hair is now thin and wispy, and the first sign of "+
      "wrinkles has begun to ravage his face. Despite that, his red eyes "+
      "still seem to blaze with a vitality unbecoming to his age.\n");
   set_stats(({60,60,60,25,25,60}));
   set_alignment(-250);
   set_knight_prestige(-3);
   set_skill(SS_WEP_KNIFE,60);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_PARRY,50);
   set_skill(SS_BLIND_COMBAT,50);
   set_skill(SS_AWARENESS,75);
   set_act_time(6);
   add_act("grin sad");
   add_act("say Please, make yourself comfortable.");
   set_cact_time(3);
   add_cact("say Iblith!");
   add_cact("snarl all");
   set_default_answer("I'm sorry, I do not understand what you ask of me.\n");
   add_ask(({"heal","healing","change","ailments","ailment"}),
      "I could change your ailments, but lately is has been "+
      "such a hardship to get all the ingredients I need. "+
      "I cannot help you.\n");
   add_speak("I am a healer of ailments both strange and disturbing.\n");
   add_prop(NPC_I_NO_RUN_AWAY,1);
   set_title("the Mage of Renown");
   /* has been removed because it conflicts with rules
   trig_new("%w 'gives' 'you' 'a' 'silver' 'coin.\n' %s","react_silver");
   trig_new("%w 'gives' 'you' 'a' 'gold' 'coin.\n' %s","react_gold");
   trig_new("%w 'gives' 'you' 'a' 'platinum' 'coin.\n' %s","react_platinum");
   Lord Korat */
}
void
arm_me()
{
   object item;
   seteuid(getuid(TO));
   item = clone_object(CPASS(arm/piwafwi));
   item -> move(TO);
   item = clone_object(CPASS(arm/dw_boots));
   item -> move(TO);
   command("wear all");
   item = clone_object(CPASS(wep/dw_dagger));
   item -> move(TO);
   command("wield all");
   MONEY_MAKE_GC(random(20))->move(TO,1);
}
int
react_silver(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_silver",who);
      return 1;
   }
}
void
return_silver(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      if(obj->query_prop(HAVE_BEEN_CHANGED))
         {
         write("The drow mage tells you he cannot change your sex more than once.\n");
         say("The drow mage says he cannot change " + QTNAME(TP) + "'s "+
            "sex more than once.\n");
      }
      else
         {
         command("emote gathers some herbs from a nearby shelf.");
         write("The drow mage crushes the herbs in his palm, then places his "+
            "hand onto your forehead and begins to chant in a strange tongue.\n");
         say("The drow mage crushes the herbs in his palm, then places his "+
            "hand onto " + QTNAME(TP) + "'s forehead and begins to chant in a "+
            "strange tongue.\n");
         obj -> set_gender(0);
         obj -> catch_msg("You feel just like a man!\n");
         say(QCTNAME(TP) + " looks just like a man!\n");
         obj -> add_prop(HAVE_BEEN_CHANGED,1);
      }
   }
}
int
react_gold(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_gold",who);
      return 1;
   }
}
void
return_gold(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      if(obj -> query_prop(HAVE_BEEN_CHANGED))
         {
         write("The drow mage tells you he cannot change your sex more than once.\n");
         say("The drow mage says he cannot change " + QTNAME(TP) + "'s sex "+
            "more than once.\n");
      }
      else
         {
         command("emote gathers some herbs from a nearby shelf.");
         write("The drow mage crushes the herbs in his palm, then places his "+
            "hand onto your forehead and begins to chant in a strange tongue.\n");
         say("The drow mage crushes the herbs in his palm, then places his "+
            "hand onto " + QTNAME(TP) + "'s forehead and begins to chant in a "+
            "strange tongue.\n");
         obj -> set_gender(1);
         obj -> catch_msg("You feel just like a woman!\n");
         say(QCTNAME(TP) + " looks just like a woman!\n");
         obj -> add_prop(HAVE_BEEN_CHANGED,1);
      }
   }
}
int
react_platinum(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_platinum",who);
      return 1;
   }
}
void
return_platinum(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      if(obj -> query_prop(HAVE_BEEN_CHANGED))
         {
         write("The drow mage tells you he cannot change your sex more than once.\n");
         say("The drow mage says he cannot change " + QTNAME(TP) + "'s sex "+
            "more than once.\n");
      }
      else
         {
         command("emote gathers some herbs from a nearby shelf.");
         write("The drow mage crushes the herbs in his palm, then places his "+
            "hand onto your forehead and begins to chant in a strange tongue.\n");
         say("The drow mage crushes the herbs in his palm, then places his "+
            "hand onto " + QTNAME(TP) + "'s forehead and begins to chant in a "+
            "strange tongue.\n");
         obj -> set_gender(2);
         obj -> catch_msg("You feel like neither a man nor a woman.\n");
         say(QCTNAME(TP) + " looks like neither a man nor a woman.\n");
         obj -> add_prop(HAVE_BEEN_CHANGED,1);
      }
   }
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob,environment()))
      {
      command("growl angrily all");
      command("kill " + (ob->query_real_name()));
   }
}