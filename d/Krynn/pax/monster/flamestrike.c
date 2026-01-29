/* Dragon by percy */
/*
   flamestrike.c
   -------------

   Copied and altered : 95/02/02
   By ................: Jeremiah

   Latest update .....: 95/04/17
   By ................: Jeremiah


   Dragon to be used in Pax Tharkas. Flamestrike is the strange 
   nursemaid guarding the children.

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
   
int heal;
int forced_attacktype = 0;


void
create_creature()
{
   int i;
   
   set_name("flamestrike");
   set_short("red dragon");
   set_race_name("dragon");
   set_adj("red");
   add_adj("ancient");
   set_gender(G_FEMALE);
   set_long("This is a huge, but old, red dragon. Her great head is " +
            "lined and wrinkled with age, the brilliant red skin " +
            "grayish and mottled. One of her eyes is almost completely " +
            "white. Long scars run along her sides, and her wings are " +
            "leathery and dry. Her talons though, are still sharp and " +
            "destructive.\n");

   for (i = 0; i < 6; i++)
   set_base_stat(i, 160 + random(20));

   set_stat_extra(3,-90);
   set_stat_extra(0,30);
   set_stat_extra(1,30);
   set_stat_extra(2,30);   

   set_hp(query_max_hp());
   
   set_skill(SS_DEFENCE, 100);
   set_knight_prestige(10);
   
   set_alignment(-200);
    
   set_attack_unarmed(0, 75, 70, W_IMPALE, 30, "bite");
   set_attack_unarmed(1, 65, 60, W_BLUDGEON, 10, "right wing");
   set_attack_unarmed(2, 65, 60, W_BLUDGEON, 10, "left wing");
   set_attack_unarmed(3, 95, 90, W_SLASH, 25, "right claw");
   set_attack_unarmed(4, 95, 90, W_SLASH, 25, "left claw");

   set_hitloc_unarmed(0, 100, 10, "head");
   set_hitloc_unarmed(1, 90, 50, "body");
   set_hitloc_unarmed(2, 90, 20, "tail");
   set_hitloc_unarmed(3, 90, 10, "right wing");
   set_hitloc_unarmed(4, 90, 10, "left wing");   


   add_prop(LIVE_I_SEE_DARK, 100);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   add_prop(CONT_I_VOLUME, 5679000);
   add_prop(CONT_I_WEIGHT, 5784000);

   set_act_time(4);
   add_act("growl");
   add_act("say What are you doing here ?");
   add_act("emote drinks some water from the huge basin.");
   add_act("emote stares intensely at you.");
   add_act("emote snarls savagely at you.");
   add_act("emote grabs a chunk of rotten meat from the huge bucket, " +
           "and swallows it.");

   set_cact_time(5);
   add_cact("say I'm not going to let you take my children.");
   add_cact("growl");
   add_cact("emote looks at you with almost insane hatred in her eyes.");
   add_cact("emote blows some smoke through her nostrils.");
   add_cact("grin");
}
 

void
attack_someone()
{
    object *who, child, woman;

    child = present("girl", E(TO));
    woman = present("maritta", E(TO));
    who   = FILTER_LIVE(all_inventory(E(TO))) - ({ TO }) - ({ child }) - 
		({ woman }); 

   if (!sizeof(who))
	return;

    command("shout My children!");
    command("kill " + OB_NAME(who[random(sizeof(who))]));
}


void
react_to_arrives(object who)
{
   if(who == present("girl", E(TO)))
      set_alarm(1.0, 0.0, attack_someone);
}


int
special_attack(object enemy)
{
   
   int attacktype, i, penet;
   mixed* hitresult;
   string how;
   object me, *ob;

   me = TO;

   if (forced_attacktype == 0)   /* no forced special attack this turn */
      attacktype = random(10);
   else
      attacktype = forced_attacktype;

   if (attacktype == 1)
   {
      if (forced_attacktype == 0)
      {
         /* Dragon inhales air, and forces next attack to be cloud breath */
      
         tell_room(E(TO),"The eyes of the dragon narrows and her nostrils " +
                   "widens.\n",TO);
         tell_room(E(TO),"You hear a sharp intake of breath.\n",TO);
         forced_attacktype = 1;
         return 1;
      }

      tell_room(E(TO),"A cloud of fire bursts from the dragons mouth. " +
                      "Your eyes sting and fills with tears, as the " +
                      "flames engulf you.\n",TO);
      
      ob =  FILTER_LIVE(all_inventory(E(me))) - ({ me });
      
      for (i = 0; i < sizeof(ob); i++)
      {
         penet = 650 + random(600);
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
         tell_watcher(QCTNAME(ob[i]) + " is " + how + " by the dragon breath!\n", ob[i]);
         
         
         if (ob[i]->query_hp() <= 0)
            ob[i]->do_die(me);
      }
      forced_attacktype = 0;
      return 1;
   }
   
   if (attacktype == 2)
   {
      if (heal == 10)
         return 0;

      if (forced_attacktype == 0)
      {
         tell_room(E(TO),"The dragon reels back, and gets a distant look " + 
                   "in her eyes.\n",TO);
         forced_attacktype = 2;
         return 1;
      }

      heal += 1;
      me->heal_hp(500);
      tell_room(E(TO),"The eyes of the dragon flares up as she throws " +
                "herself into the battle with renewed vigour.\n",TO);
      forced_attacktype = 0;
      return 1;
   }
   
   return 0;
}

