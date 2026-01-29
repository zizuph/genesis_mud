/* Dragon by percy */
/*
ember.c
-------

Copied and altered : 95/03/01
By ................: Jeremiah

Latest update .....: 95/05/19
By ................: Jeremiah


Dragon to be used in Pax Tharkas. Ember the dragon of Lord Verminaard.

Navarre March 11th 2007, Added check for who, to avoid runtimes.

*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
inherit C_FILE

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

inherit "/std/act/domove"; /* Include this if you want the creature to move */
   inherit "/std/act/action"; /* Include this if you want your creature to act */
   
int just_cloned = 1;    /* Used to avoid the double call of do_dragon_fear */
/* in both init_living and enter_env whenever the  */
/* dragon is cloned. var used in init_living()     */

int alarm_id = 0;       /* The id of the alarm that resets just_cloned     */  

int heal; 
int forced_attacktype = 0;


void
create_creature()
{
   int i;
   
   set_name("ember");
   set_short("red dragon");
   set_race_name("dragon");
   set_adj("magnificent");
   add_adj("red");
   set_gender(G_MALE);
   set_long("This is a huge, magnificent, red dragon. Strong muscles " +
      "bulge under his brilliant red skin. His teeth and talons " +
      "looks sharp and very destructive. His eyes shines with " +
      "intelligence and malevolence.\n");
   
   set_base_stat(0,280);
   set_base_stat(1,240);
   set_base_stat(2,300);
   set_base_stat(3,150);
   set_base_stat(4,180);
   set_base_stat(5,200);
   
   set_hp(query_max_hp());
   
   set_skill(SS_DEFENCE,      100);
   set_skill(SS_BLIND_COMBAT, 100);
   set_skill(SS_AWARENESS,    150);
   
   set_knight_prestige(5000);
   set_alignment(-1200);
   set_intoxicated(1000);
   
   set_attack_unarmed(0, 90, 90, W_IMPALE, 30, "bite");
   set_attack_unarmed(1, 70, 60, W_BLUDGEON, 10, "right wing");
   set_attack_unarmed(2, 70, 60, W_BLUDGEON, 10, "left wing");
   set_attack_unarmed(3, 95, 80, W_SLASH, 25, "right claw");
   set_attack_unarmed(4, 95, 80, W_SLASH, 25, "left claw");
   
   set_hitloc_unarmed(0, 100, 10, "head");
   set_hitloc_unarmed(1, 90, 50, "body");
   set_hitloc_unarmed(2, 90, 20, "tail");
   set_hitloc_unarmed(3, 90, 10, "right wing");
   set_hitloc_unarmed(4, 90, 10, "left wing");   
   
   add_prop(LIVE_I_SEE_INVIS,   100);
   add_prop(MAGIC_AM_MAGIC, ({100, "divination"}));
   add_prop(OBJ_I_RES_ACID, 40);
   add_prop(OBJ_I_RES_FIRE, 100);
   add_prop(OBJ_I_RES_ELECTRICITY, 40);
   
   add_prop(LIVE_I_SEE_DARK,   200);
   add_prop(LIVE_I_QUICKNESS,  150);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   add_prop(CONT_I_VOLUME,     5500000);
   add_prop(CONT_I_WEIGHT,     10000000);
   
   set_alarm(1200.0, 0.0, "transform");
   
   seteuid(getuid(TO));
}


int
test_friend(object who)
{
   if(who->query_race_name() == "draconian")
      return 1;
   
   if(who->query_real_name() == "verminaard")
      return 1;
   
   return 0;
}

int
special_attack(object enemy)
{
   int attacktype, i, penet;
   mixed* hitresult;
   string how;
   object me, *ob;
   
   me = this_object();
   
   if (forced_attacktype == 0)   /* no forced special attack this turn */
      attacktype = random(10);
   else
      attacktype = forced_attacktype;
   
   if (attacktype == 1)
      {
      if (forced_attacktype == 0)
         {
         /* Dragon inhales air, and forces next attack to be cloud breath */
         
         tell_room(E(TO),"The eyes of the dragon narrows and his nostrils " +
            "widens.\n",TO);
         tell_room(E(TO),"You hear a sharp intake of breath.\n",TO);
         forced_attacktype = 1;
         return 1;
       }
      
      tell_room(E(TO),"A cloud of fire bursts from the dragons mouth. " +
         "Your eyes sting and fills with tears, as the " +
         "flames scorch you.\n",TO);
      
      ob =  FILTER_LIVE(all_inventory(environment(me))) - ({ me });
      
      /* Remove friends from breath victims */
      
      for (i = 0; i < sizeof(ob); i++)
      {
         if(test_friend(ob[i]))
            ob -= ({ ob[i] });
       }
      
      for (i = 0; i < sizeof(ob); i++)
      {
         penet = 850 + random(600);
         penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_FIRE) / 100;
         hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);
         
         how = "not harmed";
         if (hitresult[0] > 0)                  
            how == "barely burned";
         if (hitresult[0] > 10)
            how = "slightly burned";
         if (hitresult[0] > 20)
            how = "burned quite badly";
         if (hitresult[0] > 40)
            how = "burned very badly";
         if (hitresult[0] > 60)
            how = "badly incinerated";
         
         ob[i]->catch_msg("You were " + how + " by the dragon breath!\n");
         tell_watcher(QCTNAME(ob[i]) + " is " + how + " by the dragon " +
            "breath!\n", ob[i]);
         
         
         if (ob[i]->query_hp() <= 0)
            ob[i]->do_die(me);
       }
      forced_attacktype = 0;
      return 1;
   }
   
   if (attacktype == 2)
      {
      if (heal == 20)
         return 0;
      
      if (forced_attacktype == 0)
         {
         tell_room(E(TO),"The dragon reels back, and gets a distant look " + 
            "in his eyes.\n",TO);
         forced_attacktype = 2;
         return 1;
       }
      
      heal += 1;
      me->heal_hp(250);
      tell_room(E(TO),"The eyes of the dragon flares up as he throws " +
         "himself into the battle with renewed vigour.\n",TO);
      forced_attacktype = 0;
      return 1;
   }
   
   
   if (attacktype == 3)
      {
      if(!random(4))
         present("verminaard", E(TO))->help_friend(enemy);
   }
   
   return 0;
}


void
dragon_fear_player(object who)
{
   
   if(who && !(QRACE(who) == "draconian") && !(QRACE(who) == "dragon") &&
      !(who->query_name() == "Verminaard"))
   {
      if(!P("Dragon_fear", who))
      {
         clone_object(POBJ + "dragon_fear")->move(who);
      }
   }
}


void
reset_just_cloned()
{
   just_cloned = 0;
}


void
init_living()
{
   ::init_living();
   
   if(just_cloned)       /* See description of variable */
      {   
      if(!alarm_id)
         alarm_id = set_alarm(2.0, 0.0, "reset_just_cloned");
      return;
   }
   
   set_alarm(1.0, 0.0, "dragon_fear_player", TP);   
}


void
dragon_fear_room()
{
   int    i;
   object me, *ob;
   
   me = TO;
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   
   for (i = 0; i < sizeof(ob); i++)
   {
      if(!(QRACE(ob[i]) == "draconian") && !(QRACE(ob[i]) == "dragon") &&
            !(ob[i]->query_name() == "Verminaard"))
      {
         if(!P("Dragon_fear", ob[i]))
            clone_object(POBJ + "dragon_fear")->move(ob[i]);
        }
   }
}


void
enter_env(object to, object from)
{
   ::enter_env(to,from);
   set_alarm(1.0, 0.0, "dragon_fear_room");
}


void
attack_enemy(object who)
{
   object pack = present("pack", E(TO));

   if(who && !query_attack() && present(who,E(TO)))
   {
      if(pack->avenir_pack() || pack->query_standard_pack())
      {
        /*An exploit with labelled backpacks from Avenir addressed in 
          appropriate fashion */

         command("say Do you take me for a fool? That you can trick " +
            "me with a container?");
         command("emote snarls furiously, incinerating " +pack->short()+ 
            " with a blast of fire!");
         pack->remove_object();
         TO->set_skill(SS_BLOCK, 100);
         TO->command("block north");
         TO->command("assist verminaard");
         TO->add_prop(LIVE_I_QUICKNESS,  200);

         object vermie = present("verminaard", E(TO));
         if(vermie)
         {
            vermie->set_skill(SS_BLOCK, 100);
            vermie->command("say We won't let this one escape!");
            vermie->command("block west");
         }
      }

      command("growl " + who->query_real_name());
      command("kill " + who->query_real_name());
      command("assist verminaard");
   }
}

void
kill_enemy(object enemy)
{
   set_alarm(3.0, 0.0, "attack_enemy", enemy);
}


void
attack_object(object ob)
{
   if (ob->query_real_name() == "verminaard")
      {
      tell_room(E(TO), "The magnificent red dragon growls, and stops the "
         + "attack.\n", TO);
      
      return;
   }
   
   ::attack_object(ob);
}


void
transform()
{
   object vermie, pyros;
   
   vermie = present("verminaard", E(TO));
   
   if(query_attack())
      {
      set_alarm(1200.0, 0.0, "transform");
      return;
   }
   
   if(vermie)
      {
      if(vermie->query_attack())
         {
         set_alarm(1200.0, 0.0, "transform");  
         return;
      }
   }
   
   tell_room(E(TO), "Suddenly the dragon starts to shrink. His huge " +
      "leathery wings dissapears into his back, the brilliant " +
      "red scales fades and vanishes, leaving pale shin behind. " +
      "The sharp talons withdraws and the figure blurs for a " +
      "few moments. A human figure stands before you.\n", TO);
   
   
   pyros = clone_object(PMONSTER + "pyros");
   if(vermie)
      {
      pyros->set_leader(vermie);
      vermie->team_join(pyros);
   }
   pyros->move(E(TO));
   remove_object();
}

public int
second_life(object killer)
   {
   K_KILL_LOG("kills", "Ember", killer);
   return 0;
}
