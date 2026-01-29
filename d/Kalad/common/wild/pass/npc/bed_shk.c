/* 
 * /d/Kalad/common/wild/pass/npc/bed_shk.c
 * Purpose    : The head bedellin of the camp. He has the oracle quest to do.
 * Located    : /d/Kalad/common/wild/pass/desert/camp/c26
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define QUEST_NAME "oraclequest"
#define CAN_DO_ORACLE_QUEST "_can_do_oracle_quest"
object bedshk;
/* by Antharanos */
void
create_monster()
{
   int i;
   set_name("musalim");
   add_name("sheik");
   set_race_name("human");
   set_adj("towering");
   add_adj("dark-skinned");
   set_short("bedellin sheik");
   set_long("A great monument of a nomad, this powerfully-built and "+
      "dignified Bedellin commands everyone in his presence with his "+
      "aura of leadership and wisdom. Although in his middle years, there "+
      "is nothing about him indicating weakness, or senility.\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 125 + random(50));
   set_base_stat(3, 75);
   set_base_stat(4, 75);
   set_base_stat(5, 115);
   set_alignment(300);
   set_knight_prestige(-2);
   set_skill(SS_WEP_SWORD,100);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,90);
   set_skill(SS_BLIND_COMBAT,60);
   set_skill(SS_AWARENESS,80);
   set_act_time(6);
   add_act("say We Iriphawa are a strong tribe.");
   add_act("say The Bedellin people are the only true people.");
   add_act("ponder many things");
   add_act("sigh");
   set_cact_time(3);
   add_cact("say May T'har eat your very soul!");
   add_cact("emote screams in outrage.");
   add_cact("emote grins brutally.");
   add_speak("I wish a brave adventurer would help my tribe. I am so "+
      "in need of help, that I am even considering berrani such as you "+
      "to aid me with my problems. Sadly, no one has proven worthy of the "+
      "holy quest that must be done.\n");
   set_default_answer("The sheik says: I do not understand your question, ulugarr.\n");
   add_ask(({"bedellin","nomads","nomad","bedellin nomads","iriphawa"}),"The sheik says: "+
      "We are a free-spirited people, we answer to noone but the gods in "+
      "our wanderings across the waste.\n");
   add_ask(({"gods","god","t'har"}),"The sheik says: T'har is the "+
      "greatest of the gods of the waste.\n");
   add_ask(({"waste","great kalad waste","great waste","kalad waste"}),
      "The sheik says: It is the motherland, where all true people live. It "+
      "is this land you are in.\n");
   add_ask(({"berrani"}),"The sheik says: That would be you.\n");
   add_ask(({"holy quest","quest"}),"The sheik says: Listen carefully "+
      "brave one, for this holy mission is the key for the survival of all "+
      "of the waste. I would undergo this mission myself, but the tribe "+
      "needs my guidance now more than ever. A terrible power is lurking "+
      "beneath the land, in the sleeping hours, nomads have without warning "+
      "suddenly disappeared, wives awake and find that their husbands and "+
      "even their children are gone, when they were sleeping just a few feet "+
      "from them. We desperately need the wisdom of the oracle, but before "+
      "that can occur, you must gather three sacred items. These items you "+
      "must use to reach the oracle. Once you have found the answer from the "+
      "oracle, whisper it to me.\n");
   add_ask(({"oracle"}),"The sheik says: After you have gathered the three "+
      "necessary items, you must journey to the Desertrise mountains. "+
      "There, on a high wind-swept peak, you shall find the sacred oracle.\n");
   add_ask(({"three sacred items","three items","sacred items","items","item"}),
      "The sheik says: The first item is located in the great salt flat "+
      "here within the waste. You must take from the foul lizard men the "+
      "sacred feather of Nathla. Then, you must go to the lonely oasis, "+
      "and fetch the urn of Rata. Lastly, and perhaps the most dangerous, "+
      "is the third and final item...the heart of the Lamia Queen. This "+
      "terrible beast is known to dwell in the rock plains at the foot of "+
      "the Desertrise mountains. Once you've recovered these items, then "+
      "seek the Oracle.\n");
   set_title("the Sheik of the Iriphawa tribe");
}
void
my_stuff()
{
   object it;
   seteuid(getuid(TO));
   it = clone_object("/d/Kalad/common/wild/pass/wep/bed_ssword");
   it -> move(TO);
   command("wield all");
   it = clone_object("/d/Kalad/common/wild/pass/arm/bed_skeff");
   it -> move(TO);
   it = clone_object("/d/Kalad/common/wild/pass/arm/bed_srobe");
   it -> move(TO);
   command("wear all");
   MONEY_MAKE_PC(random(3))->move(TO,1);
}

void
emote_hook(string emote, object actor, string adverb = 0)
{
   if (emote=="pat") set_alarm(1.0,0.0,"react_pat",actor);
   if (emote=="kick") set_alarm(1.0,0.0,"react_pat",actor);
   if (emote=="spit") set_alarm(1.0,0.0,"react_pat",actor);
   if (emote=="poke") set_alarm(1.0,0.0,"react_pat",actor);
}

void
react_pat(object who)
{
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("gasp");
      command("say How dare you lay a hand on me! Foul ulugarr!");
   }
}

void
return_quest(object who)
{
   object obj;
   if (obj = present(who, environment()))
   {
      if(obj->test_bit("Kalad",0,15))
         {
         command("chuckle");
         command("say Foolish berrani, did you truly expect to get rewarded "+
            "more than once for the same task?");
      }
      else
         {
         if(obj->query_prop(CAN_DO_ORACLE_QUEST))
            {
            command("sigh");
            command("swear");
            command("say It is as I feared.");
            command("say Thank you, " + (obj->query_nonmet_name()) + " for accomplishing this holiest of quests.\n");
            command("say May T'har grant you your fondest wish!");
            TP->catch_tell("You feel the power of T'har flow into you!\n");
            TP->catch_tell("You feel much more experienced!\n");
            obj -> add_exp(25000);
            obj -> set_bit(0,15);
            log_file(QUEST_NAME, extract(ctime(time()),4,15)+ " "+
               capitalize(TP->query_real_name()) + " rewarded with 25000 xp, "+
               "<"+TP->query_average_stat()+">average stats.\n");
            command("emote rushes out of the tent to rally his tribe against the ogres.\n");
            if(bedshk = present("musalim", environment(TP)))
               {
               bedshk -> remove_object();
            }
         }
         else
            {
            TP->catch_msg("You have not yet gone to see the Oracle!\n");
         }
      }
   }
}

/*
 * Routine speech_hook introduced by Mercade to let the player say, whisper,
 * ask or jodel the solution in any way (as long as it's directed at us).
 */
void
speech_hook(string verb, object actor, string adverb, object *oblist,
    string text, int target)
{
    if ((target == 1) && (lower_case(text) == "ogres"))
    {
        set_alarm(2.0, 0.0, &return_quest(this_player()));
    }
}

int
special_attack(object enemy)
{
   object me;
   mixed* hitresult;
   string how;
   me = TO;
   if(random(10))
      return 0;
   hitresult = enemy->hit_me(450 + random(450), W_BLUDGEON, me, -1);
   how = " narrowly affected by the attack";
   if(hitresult[0] > 0)
      how == "";
   if(hitresult[0] > 10)
      how = " slightly affected by the attack";
   if(hitresult[0] > 20)
      how = " affected badly by the attack";
   if(hitresult[0] > 30)
      how = " hurt incredibly bad";
   if(hitresult[0] > 40)
      how = " dealt a gaping, fatal wound";
   me -> catch_msg("You attempt to hit your opponent with a thunderous strike!\n" +
      capitalize(enemy->query_pronoun()) + " is struck and" +
      how + ".\n");
   enemy -> catch_msg(QCTNAME(me) + " attempts to strike you with a thunderous strike!\n" +
      "You are struck and" + how + ".\n");
   tell_watcher(QCTNAME(me) + " attempts to strike " + QTNAME(enemy) + " with a thunderous strike!\n" +
      capitalize(enemy->query_pronoun()) + " is struck and" +
      how + ".\n", enemy);
   if(enemy->query_hp() <= 0)
      enemy->do_die(me);
   return 1;
}