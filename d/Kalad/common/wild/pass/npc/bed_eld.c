/* 
 * /d/Kalad/common/wild/pass/npc/bed_eld.c
 * Purpose    : A belledin elder warrior
 * Located    : /d/Kalad/common/wild/pass/desert/camp/c20
 * Created By : Antharanos ??.??>??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <money.h>
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
   set_name("elder");
   set_race_name("human");
   set_adj("bedellin");
   set_short("bedellin elder");
   set_long("A fierce desert nomad of noble bearing and stern visage. "+
      "He has achieved the greatest status in Bedellin society, second "+
      "only to becoming Sheik, he has been honored with the title of Elder. "+
      "He is truly a man to be feared, for only the best warriors are chosen "+
      "as Elders.\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 90 + random(30));
   set_base_stat(3, 70);
   set_base_stat(4, 70);
   set_base_stat(5, 125);
   set_alignment(500);
   set_knight_prestige(-3);
   set_skill(SS_WEP_SWORD,90);
   set_skill(SS_WEP_POLEARM,90);
   set_skill(SS_WEP_KNIFE,90);
   set_skill(SS_UNARM_COMBAT,40);
   set_skill(SS_DEFENCE,80);
   set_skill(SS_PARRY,80);
   set_skill(SS_BLIND_COMBAT,80);
   set_skill(SS_AWARENESS,75);
   set_act_time(6);
   add_act("say The Sheik is very busy right now.");
   add_act("emote stands his guard vigilantly.");
   add_act("say It is a great honor to be the Sheik's guard.");
   add_act("emote paces about the room.");
   add_act("say Only important visitors may see the Sheik.");
   set_cact_time(3);
   add_cact("say Now I shall gut you and skin you like a goat!");
   add_cact("scream");
   add_cact("say T'har curse you to the fiery pits of hell!");
   add_cact("say T'har damn you to neverending suffering!");
   add_cact("say Filthy foreigner!");
   add_speak("The Sheik is very busy right now, only visitors of utmost "+
      "importance are allowed to enter and see him.\n");
   trig_new("%w 'tries' 'to' 'go' %s","react_pat");
   trig_new("%w 'spits' %s","react_spit");
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
   MONEY_MAKE_GC(random(6))->move(TO,1);
}
int
react_pat(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_pat",who);
      return 1;
   }
}
void
return_pat(string who){
   object obj;
   int ran;
   if(obj = present(who,environment())){
      command("say Foolish berrani!");
      command("kill " + (obj->query_real_name()));
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
