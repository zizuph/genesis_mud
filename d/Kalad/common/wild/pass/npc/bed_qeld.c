/* 
 * /d/Kalad/common/wild/pass/npc/bed_qeld.c
 * Purpose    : A quest npc for the poisned well quest.
 * Located    : /d/Kalad/common/wild/pass/desert/camp
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define QUEST_NAME "waterquest"
#define HAVE_DRUNK_POISON "_have_drunk_poison"
object bedqeld;
void return_quest(object ob);
 
string
random_extra()
{
   int i;
   i = random(3);
   if(i < 1)
      return "/d/Kalad/common/wild/pass/wep/bed_edag";
   else if (i < 2)
      return "/d/Kalad/common/wild/pass/wep/bed_esword";
   else
      return "/d/Kalad/common/wild/pass/wep/bed_espear";
}
/* by Antharanos */
void
create_monster()
{
   int i;
   set_name("abdul");
   add_name("elder");
   set_race_name("human");
   set_adj("bedellin");
   set_short("bedellin elder");
   set_long("A fierce desert nomad of noble bearing and stern visage. "+
      "He has achieved the greatest status in Bedellin society, second "+
      "only to becoming Sheik, he has been honored with the title of Elder. "+
      "He is truly a man to be feared, for only the best warriors are chosen "+
      "as Elders. Strangely enough, this man of great bearing is found here, "+
      "in a rather poor tent.\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 100 + random(25));
   set_base_stat(3, 70);
   set_base_stat(4, 70);
   set_base_stat(5, 125);
   set_alignment(500);
   set_knight_prestige(-3);
   set_skill(SS_WEP_SWORD,90);
   set_skill(SS_WEP_POLEARM,90);
   set_skill(SS_WEP_KNIFE,90);
   set_skill(SS_UNARM_COMBAT,40);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,90);
   set_skill(SS_BLIND_COMBAT,80);
   set_skill(SS_AWARENESS,75);
   set_act_time(6);
   add_act("ponder");
   add_act("say If only someone could check the water for me.");
   add_act("emote paces about the room.");
   add_act("sigh");
   add_act("say I have been shamed.");
   set_cact_time(3);
   add_cact("say Now I shall gut you and skin you like a goat!");
   add_cact("scream");
   add_cact("say T'har curse you to the fiery pits of hell!");
   add_cact("say T'har damn you to neverending suffering!");
   add_cact("say Filthy foreigner!");
   set_title("the Elder of the Iriphawa Tribe");
   add_speak("I fear that our sources of water are being poisoned by "+
      "foolish and perhaps malicious outlanders. I greatly wish that someone "+
      "could tell me which watering spots are poisoned.\n");
   set_default_answer("What is it you are asking me, berrani?\n");
   add_ask(({"quests","quest","tasks","task"}),"Hmm, yes I am in need "+
      "of a fool...erm brave soul to find out which of our watering holes "+
      "has been poisoned. Once this brave soul has discovered which of the "+
      "spots has been poisoned, he should return here and ask me for a "+
      "reward.\n");
   add_ask(({"water"}),"It is the life-blood of all living creatures "+
      "here in this desert waste. Nothing but genies can survive without "+
      "it.\n");
   add_ask(({"genies","genie"}),"Powerful spirits of the elements.\n");
   add_ask(({"shame"}),"I was to check the water at the watering holes, "+
      "but failed to check one cursed water hole. Fate cursed me that day, "+
      "for my entire group, save myself, fell prey to its poisonous waters. "+
      "Now I have been forbidden by our Sheik to leave the encampment, and "+
      "although I am still an elder of the tribe, I am no longer permitted "+
      "to serve him. Instead, I am consigned to remain in this hovel...\n");
   add_ask(({"reward", "for reward", "for a reward"}), "@@reward_answer", 1);
}
void
my_stuff()
{
   object item;
   int i;
   string extra;
   extra = random_extra();
   seteuid(getuid(TO));
   item = clone_object(extra);
   item -> move(TO);
   command("wield all");
   item = clone_object("/d/Kalad/common/wild/pass/arm/bed_ekeff");
   item -> move(TO);
   item = clone_object("/d/Kalad/common/wild/pass/arm/bed_erobe");
   item -> move(TO);
   command("wear all");
   MONEY_MAKE_GC(random(10))->move(TO,1);
}
 
mixed
reward_answer()
{
    string text;

    command("say Oh, you are back. Now let us see what you have accomplished.");
   set_alarm(2.0, 0.0, &return_quest(TP));
    return;
}
 
void
return_quest(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      if(obj->test_bit("Kalad",0,16))
         {
         command("laugh");
         command("say Do you take me for a fool, berrani? I will not reward "+
            "you more than once for the same task!");
      }
      else
         {
         if(obj->query_prop(HAVE_DRUNK_POISON))
            {
            command("nod sadly");
            command("say Thank you, " + (obj->query_nonmet_name()) + " for your aid.\n");
            command("say T'har shall be pleased that you've helped his favorite "+
               "tribe.");
            TP->catch_msg("You feel the power of T'har infuse your body!\n");
            TP->catch_msg("You feel more experienced!\n");
            obj -> add_exp(1000);
            obj -> set_bit(0,16);
            log_file(QUEST_NAME, extract(ctime(time()),4,15)+ " "+
               capitalize(TP->query_real_name()) + " rewarded with 1000xp, "+
               "<"+TP->query_average_stat()+">average stats.\n");
            command("emote departs the tent to warn his fellow tribesmen.\n");
            if(bedqeld = present("abdul", environment(TP)))
               {
               bedqeld -> remove_object();
            }
         }
         else
         {
            command("say You did not discover which pond was poisoned!");
            command("say You deserve no reward!");
         }
      }
   }
}
int
react_spit(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_spit",who);
      return 1;
   }
}
void
return_spit(string who){
   object obj;
   int ran;
   if(obj = present(who,environment())){
      command("growl " + (obj->query_real_name()));
      command("say Sacrilege! I will kill you for your affront!");
      command("kill " + (obj->query_real_name()));
   }
}
int
special_attack(object enemy)
{
   object me;
   mixed* hitresult;
   string how;
   me = TO;
   if(random(6))
      return 0;
   hitresult = enemy->hit_me(100 + random(800), W_IMPALE, me, -1);
   how = " with no obvious results";
   if(hitresult[0] > 0)
      how == "";
   if(hitresult[0] > 10)
      how = " and left shaken by the assault";
   if(hitresult[0] > 20)
      how = " and left reeling from the assault";
   if(hitresult[0] > 30)
      how = " and nearly massacred into little fragments";
   if(hitresult[0] > 40)
      how = " and smashed so hard that fragments and splinters of bone and flesh are strewn about the room";
   me->catch_msg("You strike your opponent with a critical blow!\n" +
      capitalize(enemy->query_pronoun()) + " is struck with a critical blow" +
      how + ".\n");
   enemy -> catch_msg(QCTNAME(me) + " strikes you with a critical blow!\n" +
      "You are struck with a critical blow" + how + ".\n");
   tell_watcher(QCTNAME(me) + " strikes " + QTNAME(enemy) + " with a critical blow!\n" +
      capitalize(enemy->query_pronoun()) + " is struck with a critical blow" +
      how + ".\n", enemy);
   if(enemy->query_hp() <= 0)
      enemy->do_die(me);
   return 1;
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob,environment()))
      {
      command("say Mat ghashim ulugarr!");
      command("kill " + (ob->query_real_name()));
   }
}
