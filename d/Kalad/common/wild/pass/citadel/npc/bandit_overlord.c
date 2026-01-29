/*	Created by:	Antharanos
 *	Purpose:
 *	Modified by:	Toby, 97-09-17 (Made a check if Goliath can see the player,
 *			and if it is dark in the room.
 *                      Cotillion, 2019-04-03 - clone_unique
 */

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
inherit "/lib/unique";

#include "/d/Kalad/defs.h"


object axe;

void
create_monster()
{
   int i;
   set_name("goliath");
   add_name("overlord");
   set_living_name("goliath");
   set_race_name("half-ogre");
   set_adj("massive");
   add_adj("menacing");
   set_long("A large being, standing well over seven feet in height. "+
      "From a distance he seems passable as a human being, but upon closer "+
      "inspection you realize that ogre blood runs through this being's "+
      "veins. Although hulking and nearly as massive as a true ogre, he has "+
      "a certain look of intelligence in his eyes, and it isn't one of "+
      "benevolence.\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 120 + random(50));
   set_base_stat(3, 60);
   set_base_stat(4, 60);
   set_base_stat(5, 150);
   set_alignment(-400);
   set_skill(SS_WEP_AXE,100);
   set_skill(SS_WEP_KNIFE,100);
   set_skill(SS_UNARM_COMBAT,60);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_PARRY,100);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_AWARENESS,75);
   set_skill(SS_SPELLCRAFT,20);
   set_act_time(6);
   add_act("snarl");
   add_act("growl");
   add_act("grin demon");
   add_act(({"smirk","wipe"}));
   add_act(({"impress","strut"}));
   add_act("shave");
   add_act("axelick");
   set_cact_time(3);
   set_title("the Chief of the Brigands");
   set_knight_prestige(1000);


    equip(({ 
                ("/d/Kalad/common/wild/pass/citadel/arm/mbgslarm"),
                ("/d/Kalad/common/wild/pass/citadel/arm/mbgloves"),
                ("/d/Kalad/common/wild/pass/citadel/arm/mbgboots"),
                clone_unique("/d/Kalad/common/wild/pass/citadel/wep/mbgaxe", 8, "/d/Kalad/common/wild/pass/citadel/wep/alt_axe"),
                ("/d/Kalad/common/wild/pass/citadel/wep/goliath_dagger")
    }));

   MONEY_MAKE_PC(random(2))->move(TO,1);
}

void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
   {
      command("shout Kill that little bugger!");
   }
}

int
special_attack(object enemy)
{
   object me;
   mixed* hitresult;
   string how;
   me = TO;
   if (random(5))
      return 0;
   hitresult = enemy->hit_me(600, W_BLUDGEON, me, -1);
   how = " without effect";
   if (hitresult[0] > 0)
      how == "";
   if (hitresult[0] > 5)
      how = " hard";
   if (hitresult[0] > 10)
      how = " very hard";
   if (hitresult[0] > 15)
      how = " extremely hard";
   if (hitresult[0] > 20)
      how = " tremendously hard";
   if (hitresult[0] > 25)
      how = " so hard, the sound of bones snapping can be heard";
   if (hitresult[0] > 30)
      how = " so incredibly hard, that blood explodes everywhere";
   me -> catch_msg("You bearhug your opponent!\n"+
      capitalize(enemy->query_pronoun())+" is bearhugged"+
      how + ".\n");
   enemy -> catch_msg(QCTNAME(me) + " bearhugs you!\n"+
      "You are bearhugged" + how + ".\n");
   tell_watcher(QCTNAME(me) + " bearhugs " + QTNAME(enemy) + "!\n"+
      capitalize(enemy->query_pronoun()) + " is bearhugged"+
      how + ".\n", enemy);
   if (enemy->query_hp() <= 0)
      enemy->do_die(me);
   /* we check if we still have the axe wielded */
   if (!axe->query_wielded())
      TO->command("wield dagger");
   return 1;
}

init_living()
{
   ::init_living();
   if (TP->query_alignment() > 100 )
      set_alarm(2.0,0.0,"attack_enemy",TP);
   else
      set_alarm(2.0,0.0,"greet_friend",TP);
}

attack_enemy(ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("say Kill that "+ ob->query_race_name()+"!");
      set_alarm(1.0,0.0,"do_attack",ob);
   }
   return;
}

do_attack(object ob)
{
   int i;
   object *friends;
   if (!ob || !present(ob, E(TO))) return;
   friends = FILTER_LIVE(all_inventory(E(TO)));
   for (i=0; i<sizeof(friends); i++)
   {
      if (friends[i]->query_name()=="Brigand" ||
            friends[i]->query_name()=="Ogre")
      {
         friends[i]->command("kill "+lower_case(ob->query_real_name()));
        }
   }
}


greet_friend(ob)
{
   if (ob && present(ob, environment()) &&
      !ob->query_npc() && random(4)>1 && CAN_SEE(TO,ob) && CAN_SEE_IN_ROOM(TO))
   {
      if (!query_attack())
         {
        command("say Greetings, "+ob->query_race_name()+".");
         return;
       }
      else
         {
        command("say Ahh, "+ob->query_race_name()+
            ". You came in time to share the loot of this "+
            "idiot here!");
         return;
       }
      return;
   }
   return;
}
