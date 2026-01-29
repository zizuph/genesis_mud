/*
   Solace lake.

   evil_cleric.c
   -------------

   Coded ........: 95/06/17
   By ...........: Jeremiah
   
   Latest update : 95/06/19
   By ...........: Jeremiah

   Evil cleric in tent in the camp at Solace lake.

*/

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h";
#include "/d/Krynn/solace/lake/local.h";
inherit M_FILE

inherit "/std/act/domove";  /* Allows cleric to move */
inherit "/std/act/action";  /* Allows cleric to act  */

int darts, heal;

void
create_krynn_monster()
{
   string str;

   set_name("evil cleric");
   set_race_name("human");
   set_long("A stout, broad shouldered, swarthy human with vaguely " +
            "squinting eyes. He is wearing the colours of the red " +
            "dragon army. He doesn't look like the normal human " +
            "mercenaries hired into the dragonarmies. There is something " +
            "strange about this man.\n");

   add_name(({"human", "man", "cleric"}));
   set_adj("broad-shouldered");
   add_adj("stout"); 
   set_gender(G_MALE);
   add_prop(OBJ_I_COLORABLE, 1);

   set_stats(({90,110,90,100,100,100}));
   set_skill(SS_DEFENCE,        80);
   set_skill(SS_PARRY,          70);
   set_skill(SS_WEP_CLUB,       90);
   set_skill(SS_UNARM_COMBAT,   30);
   set_skill(SS_BLIND_COMBAT,   40);
   set_skill(SS_AWARENESS,      50);

   add_prop(OBJ_I_RES_POISON, 30);
   add_prop(OBJ_I_RES_MAGIC,    20);
   add_prop(NPC_I_NO_RUN_AWAY,  1);

   set_alignment(-600 -random(200));
   set_knight_prestige(1200);

   set_all_hitloc_unarmed(35);

   set_act_time(3);
   add_act("peer all");
   add_act("say Takhisis will soon return to these lands.");
   add_act("say Get out!");
   add_act("cackle");
   add_act(({"stare", "say Yes my queen, I will do as you bid."}));
   add_act(({"say Darkness, soothing darkness will spread.", "cackle"}));
   add_act("say Nothing can stop her now.");
   add_act("emote mumbles a prayer.");

   darts = 3 + random(3);
   heal = 0;
   seteuid(getuid(TO));
}	

equip_me()
{
    object armour1, armour2, boots, shield, weapon;

    armour1 = clone_object("/d/Krynn/solamn/splains/obj/barmour1");
    armour1->set_color("red");
    armour1->move(TO);

    armour2 = clone_object("/d/Krynn/solamn/splains/obj/bleggings");
    armour2->set_color("red");
    armour2->move(TO);

    boots = clone_object("/d/Krynn/solamn/splains/obj/bboots");
    boots->move(TO);

    shield = clone_object("/d/Krynn/solamn/splains/obj/blargeshield");
    shield->set_color("red");
    shield->move(TO);

    weapon = clone_object(OBJ + "bmace");
    weapon->set_color("red");
    weapon->move(TO);

    command("wear all");
    command("wield all");
    command("remove shield");
}


void
start_the_poison(object poison)
{
    poison->start_poison();
}


void
remove_dart()
{
   tell_room(E(TO), "The dart vanishes as if it had never existed.\n",
      TO);
}

 
int
special_attack(object enemy)
{
   int    attacktype, penet, wloc;
   string *woundloc; /* location where wounded */
   mixed  hitresult;
   string how, tmp;   
   object *nomsg, *enemies;
   object victim, poison;

   woundloc = ({"head", "left arm", "right arm", 
                "body", "left leg", "right leg"});
   nomsg = ({ TO , enemy });

   attacktype = random(15);

   if (attacktype == 1)  /* poisonous dart  */
   {
       if(!darts)
          return 0;

       enemies = TO->query_enemy(-1);
       victim = enemies[random(sizeof(enemies))];
       wloc = random(6);

       victim->catch_msg("Suddenly " + QTNAME(TO) + " jerks his " +
          "free hand and throws a tiny dart at you. The dart hits " +
          "you in your " + woundloc[wloc] + ".\n");

       tell_room(E(TO), QCTNAME(TO) + " suddenly jerks his free hand " +
          "and throws a tiny dart at " + QCTNAME(victim) + ". The " +
          "dart hits " + OBJECTIVE(victim) + " in the " + woundloc[wloc] +
          ".\n", nomsg); 

       poison = clone_object(OBJ + "dartpoison");
       poison->move(victim);
       set_alarm(2.0, 0.0, "start_the_poison", poison);
       set_alarm(4.0, 0.0, "remove_dart");

       darts--;
       if(!darts)
          command("wear shield");     

       return 1;
   }

   if (attacktype == 2)  /* cause wound     */
   {

      enemy->catch_msg(QCTNAME(TO) + " looks intently at you and " +
         "mumbles a strange prayer.\n");

      tell_room(E(TO), QCTNAME(TO) + " looks intently at " +
         QCTNAME(enemy) + " and mumbles a strange prayer.\n", nomsg);
 
      penet = 500 + random(200);
      penet -= penet * enemy->query_magic_res(MAGIC_I_RES_MAGIC) / 100;
      hitresult = enemy->hit_me(penet, MAGIC_DT, TO, -1);

      how = "";
      if (hitresult[0] > 0)
         how = "tiny";
      if (hitresult[0] > 10)
         how = "shallow";
      if (hitresult[0] > 20)
         how = "nasty";
      if (hitresult[0] > 40)
         how = "serious";
      if (hitresult[0] > 60)
         how = "gaping";

      wloc = random(6);

      if (hitresult[0] > 0)
      {
         enemy->catch_msg("You feel a pain running through your " +
            woundloc[wloc] + " as a " + how + " wound suddenly " +
            "appears out of nowhere.\n");

         tell_watcher(QCTNAME(enemy) + " writhes in pain as a " + how +
            " wound suddenly appears on " + POSSESSIVE(enemy) + " " +
            woundloc[wloc] + ".\n", enemy);
      }
      else
      {
         enemy->catch_msg("You feel a pain running through your " +
            woundloc[wloc] + ".\n");

         tell_watcher(QCTNAME(enemy) + " suddenly writhes in pain.\n",
            enemy);
      }     

      if (enemy->query_hp() <= 0)
      {
         tmp = enemy->query_nonmet_name();
         enemy->do_die(TO);
         command("cackle");
         tell_room(E(TO), QCTNAME(TO) + " kicks the lifeless body of " +
            tmp + ".\n", TO);
      }
 
      return 1;
   }

   if (attacktype == 3)  /* heal wounds(TO) */
   {
      if (heal == 10)
         return 0;

      heal++;
      TO->heal_hp(200);
      command("swear");
      tell_room(E(TO), QCTNAME(TO) + " concentrates deeply and " +
         "mumbles some strange words under his breath.\n",TO);
      command("emote smiles wickedly");

      return 1;
   } 

   return 0;
}


void
attacked_by(object ob)
{
   ::attacked_by(ob);
}

