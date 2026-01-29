/* 
 * /d/Kalad/common/wild/pass/npc/bed_healer.c
 * Purpose    : The healer of the bedellin. He once healed players, but until the correct price has been implimented, I have disabled it.
 * Located    : /d/Kalad/common/wild/pass/desert/camp/c33
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define HAVE_BEEN_HEALED "_have_been_healed"
/* This is the tribal shaman/healer in the Bedellin tribe */
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("yusuf");
   add_name("healer");
   set_race_name("human");
   set_adj("bedellin");
   set_short("bedellin healer");
   set_long("A man of wise and noble countenance, his aged and weathered "+
      "features speak of a lifetime of experiences in the desert waste.\n");
   set_stats(({50,50,50,100,150,50}));
   set_alignment(750);
   set_knight_prestige(-5);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_BLIND_COMBAT,50);
   set_skill(SS_AWARENESS,75);
   set_act_time(6);
   add_act("smile kindly all");
   add_act("say Welcome to my humble abode.");
   add_act("emote sits patiently on one side of the tent.");
   set_cact_time(3);
   add_cact("sigh");
   add_cact("say I had hoped you were wiser than this.");
   add_cact("emote looks quite disappointed with you.");
   set_default_answer("I'm sorry, I do not understand what you ask of me.\n");
   add_ask(({"heal","healing"}),
      "I can heal you of wounds. For one copper coin I shall tend to your "+
      "light wounds. For one silver coin I shall heal more serious wounds. "+
      "For one gold coin I shall heal grievous wounds. Finally, for one "+
      "platinum coin I will heal you of life-threatening wounds. I can heal "+
      "you but once, for that is the decree of the wise one, T'har.\n");
   add_speak("I am but a simple healer of the wise god, T'har.\n");
   add_prop(NPC_I_NO_RUN_AWAY,1);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   set_title("the Wise Healer of T'har");
}
void
my_stuff()
{
   object item;
   seteuid(getuid(TO));
   item = clone_object(CPASS(arm/bed_h_med));
   item -> move(TO);
   item = clone_object(CPASS(arm/bed_keff));
   item -> move(TO);
   item = clone_object(CPASS(arm/bed_robe));
   item -> move(TO);
   command("wear all");
}
int
react_copper(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_copper",who);
      return 1;
   }
}
void
return_copper(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      if(obj->query_prop(HAVE_BEEN_HEALED))
         {
         write("The bedellin healer tells you he cannot heal you more than once.\n");
         say("The bedellin healer says he cannot heal " + QTNAME(TP) + " more "+
            "than once.\n");
      }
      else
         {
         command("say Praise be to T'har.");
         write("The bedellin healer places his left hand upon your forehead and "+
            "begins to chant a spell of healing.\n");
         say("The bedellin healer places his left hand upon " + QTNAME(TP) + "'s "+
            "forehead and begins to chant a strange spell of healing.\n");
         obj -> heal_hp(100);
         obj -> catch_msg("You feel a bit better.\n");
         say(QCTNAME(TP) + " looks a bit better.\n");
         obj -> add_prop(HAVE_BEEN_HEALED,1);
      }
   }
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
      if(obj->query_prop(HAVE_BEEN_HEALED))
         {
         write("The bedellin healer tells you he cannot heal you more than once.\n");
         say("The bedellin healer says he cannot heal " + QTNAME(TP) + " more "+
            "than once.\n");
      }
      else
         {
         command("say Praise be to T'har.");
         write("The bedellin healer places his left hand upon your forehead and "+
            "begins to chant a spell of healing.\n");
         say("The bedellin healer places his left hand upon " + QTNAME(TP) + "'s "+
            "forehead and begins to chant a strange spell of healing.\n");
         obj -> heal_hp(500);
         obj -> catch_msg("You feel better.\n");
         say(QCTNAME(TP) + " looks better.\n");
         obj -> add_prop(HAVE_BEEN_HEALED,1);
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
      if(obj -> query_prop(HAVE_BEEN_HEALED))
         {
         write("The bedellin healer tells you he cannot heal you more than once.\n");
         say("The bedellin healer says he cannot heal " + QTNAME(TP) + " more "+
            "than once.\n");
      }
      else
         {
         command("say Praise be to T'har.");
         write("The bedellin healer places his left hand upon your forehead and "+
            "begins to chant a spell of healing.\n");
         say("The bedellin healer places his left hand upon " + QTNAME(TP) + "'s "+
            "forehead and begins to chant a strange spell of healing.\n");
         obj -> heal_hp(1000);
         obj -> catch_msg("You feel much better.\n");
         say(QCTNAME(TP) + " looks much better.\n");
         obj -> add_prop(HAVE_BEEN_HEALED,1);
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
      if(obj -> query_prop(HAVE_BEEN_HEALED))
         {
         write("The bedellin healer tells you he cannot heal you more than once.\n");
         say("The bedellin healer says he cannot heal " + QTNAME(TP) + " more "+
            "than once.\n");
      }
      else
         {
         command("say Praise be to T'har.");
         write("The bedellin healer places his left hand upon your forehead and "+
            "begins to chant a spell of healing.\n");
         say("The bedellin healer places his left hand upon " + QTNAME(TP) + "'s "+
            "forehead and begins to chant a strange spell of healing.\n");
         obj -> heal_hp(2500);
         obj -> catch_msg("You feel much more better then before.\n");
         say(QCTNAME(TP) + " looks much more better than before.\n");
         obj -> add_prop(HAVE_BEEN_HEALED,1);
      }
   }
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob,environment()))
      {
      command("emote looks horrified!");
      command("kill " + (ob->query_real_name()));
   }
}