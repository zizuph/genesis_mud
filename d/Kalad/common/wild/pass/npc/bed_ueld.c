/* 
 * /d/Kalad/common/wild/pass/npc/bed_ueld.c
 * Purpose    : A quest npc, he gives out the find the loot from goblin quest, which allows player to see the shiek
 * Located    : /d/Kalad/common/wild/pass/desert/camp/c20
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
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
   set_name("sabkhat");
   add_name("elder");
   set_race_name("human");
   set_adj("bedellin");
   set_short("bedellin elder");
   set_long("A fierce desert nomad of noble bearing and stern visage. "+
      "He has achieved the greatest status in Bedellin society, second "+
      "only to becoming Sheik, he has been honored with the title of Elder. "+
      "This particular man looks to be unusually wise and honorable, even "+
      "for an elder of the tribe. As such, he is to be feared, as well as "+
      "respected.\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 100 + random(30));
   set_base_stat(3, 70);
   set_base_stat(4, 75);
   set_base_stat(5, 125);
   set_alignment(400);
   set_knight_prestige(-2);
   set_skill(SS_WEP_SWORD,90);
   set_skill(SS_WEP_POLEARM,90);
   set_skill(SS_WEP_KNIFE,90);
   set_skill(SS_UNARM_COMBAT,40);
   set_skill(SS_DEFENCE,90);
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
   add_speak("The Sheik is extremely busy at the moment, and it is "+
      "doubtful that he would wish to see one such as you. However...if "+
      "you were to do a great service to the tribe, then perhaps I would "+
      "allow you to see him.\n");
   set_default_answer("The bedellin elder says: What was that, berrani?\n");
   add_ask(({"great service","service"}),"The bedellin elder says: We "+
      "Bedellin occasionally trade with the ulugarr that live in Kabal. "+
      "It was during one such trading expedition that tragedy befell. Our "+
      "entire caravan was massacred by filthy goblins! The little brutes "+
      "made away with all our valueable goods. If you are able to recover "+
      "our goods, then you would truly be worthy to see the Sheik.\n");
   add_ask(({"sheik"}),"The bedellin elder says: His name is Musalim.\n");
   add_ask(({"goblins","goblin"}),"The bedellin elder says: I am not "+
      "certain of the lair of those foul blights on Kalad, but I believe "+
      "they are somewhere in the foothills at the very western edge of the "+
      "waste.\n");
   add_ask(({"great kalad waste","great waste","kalad waste","waste"}),
      "The bedellin elder says: We call this vast desert, the motherland, "+
      "for it has supported and nurtured us.\n");
   add_ask(({"ulugarr"}),"The bedellin elder says: Why, that would be you!\n");
   add_ask(({"t'har"}),"The bedellin elder says: T'har is the great "+
      "sun god of the waste, it is through his will that we all live... "+
      "and die.\n");
   add_ask(({"kabal","city"}),"The bedellin elder says: That is where all "+
      "these foolish ulugarr are from, just like yourself.\n");
   set_title("the Elder of the Iriphawa tribe");
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   trig_new("%w 'tries' 'to' 'go' %s","react_pat");
   trig_new("%w 'spits' %s","react_spit");
   trig_new("%w 'gives' 'you' 'a' 'corpse' 'of' %s","react_corpse");
   trig_new("%w 'gives' 'you' 'a' 'large' 'pile' 'of' %s","react_pass");
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
react_corpse(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_corpse",who);
      return 1;
   }
}
void
return_corpse(string who)
{
   object obj;
   int ran;
   if(obj = present(who,environment()))
      {
      command("smirk");
      command("give corpse to " + (obj->query_real_name()));
   }
}
int
react_pass(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_pass",who);
      return 1;
   }
}
void
return_pass(string who)
{
   object obj;
   int ran;
   if(obj = present(who,environment()))
      {
      command("smile " + (obj->query_real_name()));
      command("say You may see the Sheik now.\n");
      TP->move_living("further into the tent","/d/Kalad/common/wild/pass/desert/camp/c26");
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