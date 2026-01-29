/*
 * By Korat
 * September 1996
 * 
 * A medium brigand placed in the citadel
 *
*/

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"

string
random_extra()
{
   int i;
   i = random(3);
   if(i < 1)
      return "/d/Kalad/common/caravan/wep/gmace";
   else if (i < 2)
      return "/d/Kalad/common/caravan/wep/gsword";
   else
      return "/d/Kalad/common/caravan/wep/gaxe";
}

void
create_monster()
{
   int i;
   set_name("brigand");
   set_race_name("human");
   set_adj("filthy");
   add_adj("unkempt");
   set_short("brigand");
   set_pshort("brigands");
   set_long("He is a tall, dark-haired man whose job is to "+
      "rob and steal from anyone who dares come near him. "+
      "You notice that his weapons are of the brand the "+
      "city-guards of Kabal wields. Undoubtedly they were "+
      "not given to him.\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 50 + random(25));
   set_base_stat(3, 30);
   set_base_stat(4, 30);
   set_base_stat(5, 100);
   set_alignment(-333);
   set_skill(SS_WEP_CLUB, 70);
   set_skill(SS_WEP_SWORD, 60);
   set_skill(SS_WEP_AXE, 75);
   set_skill(SS_WEP_KNIFE, 60);
   set_skill(SS_2H_COMBAT, 75);
   set_skill(SS_DEFENCE, 75);
   set_skill(SS_PARRY, 75);
   set_skill(SS_AWARENESS,40);
   set_act_time(10);
   add_act("emote looks at your equipment with greedy eyes.");
   add_act("whisper brigand something");
   add_act("emote whispers Soon a caravan will arrive ...");
   add_act("say Those guardsmen are so easy to kill.");
   add_act("say Shut up!");
   set_cact_time(3);
   add_cact("cackle");
   add_cact("grin demon");
   add_cact("shout Die now and die fast!");
   add_cact("shout It shall be a pleasure to sell your equipment!");
   add_cact("shout Lets slaughter this creature!");
   add_speak("Speak with my boss. Not me!\n");
   set_knight_prestige(200);
   set_default_answer("The brigand says: Shut up!\n");
}
void
arm_me()
{
   object wep, arm;
   int i;
   string extra;
   extra = random_extra();
   seteuid(getuid(TO));
   arm = clone_object("/d/Kalad/common/caravan/arm/gchain");
   arm -> move(TO);
   arm = clone_object("/d/Kalad/common/caravan/arm/ghelm");
   arm -> move(TO);
   command("wear all");
   wep = clone_object(extra);
   wep -> move(TO);
   wep = clone_object("/d/Kalad/common/caravan/wep/gdagger");
   wep -> move(TO);
   command("wield all");
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      if (F_DARE_ATTACK(TO,ob)) /* we dare to attack it */
         {
         command("spit " + (ob->query_real_name()));
         command("kill " + lower_case(ob->query_real_name()));
       }
      else
         {
         switch (random(4))
         {
         case 0: command("emote screams up in fright!"); break;
         case 1: command("emote whimpers: It's too big! Lets run !!"); break;
         case 2: command("emote tries to hide himself."); break;
         case 3: command("emote freezes up in fright."); break;
         default: break;
         }
      }
   }
}

/* function: do_die
 * description: We tell our boss, goliath, that we died.
 *              This will make him interfere in the battle.
 */
void
do_die(object enemy)
{
   object goliath;
   if (TO->query_hp()>0) return;

   switch (random(4))
   {
   case 0: command("say This one is lethal!!!"); break;
   case 1: command("scream"); break;
   case 2: command("panic"); break;
   case 3: command("emote screams: Heeeellllpp!"); break;
   default: break;
   }

   goliath = present("goliath", E(TO));
   if(objectp(goliath))
   {
       goliath->command("say I better help you out then!");
       goliath->command("kill "+lower_case(enemy->query_real_name()));
   }
   ::do_die(enemy);

}