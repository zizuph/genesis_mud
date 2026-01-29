inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define QUEST_NAME "coffeequest"
int kettle;
string long;
/* by Korat, parts borrowed from Antharanos */
create_monster()
{
   ::create_monster();
   set_name("karoth");
   add_name("manager");
   set_race_name("dwarf");
   set_adj("tough");
   add_adj("battle-hardened");
   set_long("This old dwarf is a former slave gladiator that "+
      "has been given the task of administrating the arena. "+
      "Even though he currently is working behind a desk, he "+
      "was once the champion of the gladiator arena of Kabal; "+
      "You still see the signs of a great fighter in him.\n");
   
   set_stats(({120,150,150,60,60,120}));
   set_alignment(0);
   set_skill(SS_WEP_CLUB,100);
   set_skill(SS_WEP_AXE,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_PARRY,100);
   set_skill(SS_AWARENESS,70);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_2H_COMBAT,100);
   
   add_prop(CONT_I_WEIGHT, 80000);  /* weights 80 kilo's */
   add_prop(CONT_I_HEIGHT, 160);    /* 160 cm high */
   set_hp(query_max_hp()); /* heal fully */
   set_title("The Manager of the Kabal arena");
   add_speak("Unfortunately, the arena is not ready for the games.\n");
   
   add_ask(({"drink","thirsty"}),"karoth says: Yes I am thirsty! "+
      "Maybe you can get me a cup of fresh coffee to ease my "+
      "stommack?\n");
  add_ask("coffee","The dwarf says: Oh yes, please get me some coffee.\n");
  add_ask(({"help","task"}),"A task? Hmm...well I am not sure. Maybe get me some coffee?\n");
   add_ask(({"fight","arena","games","participate"}),
      "Well right now the arena is closed. Come back later...\n");
   
   set_act_time(3);
   add_act(({"emote appraises you thoroughly.",
            "say Are you here to fight in the arena?",
            "smile hopefully"}));
   add_act(({"ponder what shall I do...","sigh"}));
   add_act("emote starts to leaf through the papers on his desk.");
   add_act("emote takes up a sheet, reads it slowly and then "+
      "crumbles it into a ball before dropping it back down again");
   add_act("headbutt");
   add_act(({"emote almost falls asleep while studying his papers",
            "say Ohh how I need some coffee now!"}));
   set_cact_time(1);
   add_cact("say You fool! You shall die now!");
   add_cact("headbutt");
   add_cact(({"say Ahh finally some fun!! It will be a pleasure "+
            "to rip your guts out and feed it to the lions.","cackle"}));
   
   
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   set_knight_prestige(0);
   set_default_answer("The dwarf looks at you with a wondering expression.\n");
   
   trig_new("%w 'attacks' %s", "react_attack");
}

void
arm_me()
{
   object wep, arm;
   seteuid(getuid(TO));
   arm = clone_object("/d/Kalad/common/central/arm/karoth_helm");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/central/arm/karoth_greav");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/central/arm/karoth_gaunt");
   arm -> move(TO);
   command("wear all");
   wep = clone_object("/d/Kalad/common/central/wep/karoth_axe");
   wep -> move(TO);
   command("emote fetches his weapons from the rack.\n");
   command("wield all");
   MONEY_MAKE_GC(random(10))->move(TO,1);
   MONEY_MAKE_PC(random(5))->move(TO,1);
}

kettle_return()
{
   kettle = 1;
}

public void
enter_inv(object ob, object from)
{
   object *content;
   if (MASTER_OB(ob) != "/d/Kalad/common/central/obj/kettle")
      {
      ::enter_inv(ob, from);
      set_alarm(2.0,0.0,"drop_the_object",ob);
      return;
   }
   if (!interactive(from))
      return;
   else
      set_this_player(from);
   if (from->test_bit("Kalad", 1, 0))
      {
      write(query_The_name(from) + " peers at you and says: You have helped me enough; "+
         "I cannot accept more from you.\n");
      return;
   }
   content = all_inventory(ob);
   if (sizeof(content)==0 || content[0]->query_prop("_korat_quest_coffee") != 1)
      {
      ::enter_inv(ob, from);
      write("The battle-hardened dwarf sniffs at the content of the kettle ...\n");
      write("The dwarf says: You call this coffee??\n");
      write("The dwarf sighs.\n");
      TP->catch_msg("You don't feel more experienced.\n");
      return;
   }
   ::enter_inv(ob, from);
   write("The dwarf says: Ahh, this smells like good coffee!\n");
   TO->command("drink coffee from kettle");
   TP->catch_msg("You feel more experienced.\n");
   TP->add_exp(1000);
   TP->set_bit(1,0);
   seteuid(getuid(TO));
   log_file(QUEST_NAME, extract(ctime(time()),4,15) + " "+
      capitalize(TP->query_real_name()) + " rewarded with 1000 xp,"+
      "<"+TP->query_average_stat()+"> average stats.\n");
}

int
react_aim(object who)
{
   object obj;
   int ran;
   if(who){
      if(obj = present(who, environment())){
         command("fume " + (obj->query_real_name()));
         switch(random(5))
         {
            case 0:
            command("say I hope that really hurts!\n");
            break;
            case 1:
            command("emote licks some of the blood that "+
               "drips down from his helmet.\n");
            break;
            case 2:
            command("say Don't think it will be you hurting me next time!\n");
            break;
            case 3:
            command("emote crouches a bit and tries to dodge your hits with his battleaxe.\n");
            break;
            case 4:
            command("say Getting lucky ehh? You will soon run out of that!\n");
            break;
            case 5:
            command("emote You wretch! I shall boil your blood and drink it for breakfast!\n");
            break;
         }
      }
      return 1;
   }
}

int
react_attack(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_attack",who, dummy);
      return 1;
   }
}
void
return_attack(string who,string dummy){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      if (dummy=="you!\n")
         {
         command("say How dare you to attack me!");
         command("say Die then " + obj->query_nonmet_name() + "!");
         command("kill " + (obj->query_real_name()));
         command("ponder fools, thinks they can beat me!");
         command("laugh all");
      }
      else
         {
         command("say Stop fighting in my office! Save it to the arena, fools.");
      }
   }
}


int
special_attack(object enemy)
{
   object me;
   mixed* hitresult;
   string how;
   me = this_object();
   if (random(5))
      return 0;
   hitresult = enemy->hit_me(300 + random(200), W_BLUDGEON, me, -1);
   how = " loosely";
   if (hitresult[0] > 0)
      how == " ";
   if (hitresult[0] > 10)
      how = " roughly";
   if (hitresult[0] > 20)
      how = " powerfully";
   if (hitresult[0] > 30)
      how = " smashingly";
   if (hitresult[0] > 40)
      how = " bonecrushingly";
   
   me -> catch_msg("You headbutt your opponent!\n" +
      capitalize(enemy->query_pronoun()) + " is"+ how + " headbutted by Karoth.\n");
   enemy -> catch_msg(QCTNAME(me) + " headbutts you!\n" +
      "You are hit" + how + ".\n");
   tell_watcher(QCTNAME(me) + " headbutts " + QTNAME(enemy) + "!\n" +
      capitalize(enemy->query_pronoun()) + " is headbutted" +
      how + ".\n", enemy);
   if (enemy->query_hp() <= 0)
      enemy -> do_die(me);
   set_alarm(1.0,0.0,"react_aim",enemy);
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