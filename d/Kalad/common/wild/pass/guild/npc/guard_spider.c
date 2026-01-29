#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
inherit C_FILE
inherit "/std/combat/unarmed";
int heal;
void
create_creature()
{
   set_name("spider");
   set_short("guardian spider");
   set_race_name("spider");
   set_adj("huge");
   set_gender(G_NEUTER);
   set_long("A huge spider towering 15 feet into the air. It is glowing "
      +"with a bluish flame, and its mandibles are dripping a green "
      +"viscous fluid. It is standing erect on its back 4 legs, "
      +"acting as a guard for the Drow Academy. If you are not a "
      +"member do not attempt to pass. These mystical constructs will "
      +"not permit non-belivers pass, and will destroy all who try "
      +"to enter against the will of Lloth.\n");
   set_stats(({ 200, 200, 200, 75, 0, 160}));
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_AWARENESS,100);
   set_knight_prestige(2500);
   set_alignment(0);
   set_attack_unarmed(0, 50, 50, W_BLUDGEON, 30, "right front leg");
   set_attack_unarmed(1, 50, 50, W_BLUDGEON, 30, "left front leg");
   set_attack_unarmed(2, 45, 45, W_BLUDGEON, 5, "right middle leg");
   set_attack_unarmed(3, 45, 45, W_BLUDGEON, 5, "left middle leg");
   set_attack_unarmed(4, 60, 60, W_IMPALE, 30, "mandible");
   set_hitloc_unarmed(1, 75, 15, "head");
   set_hitloc_unarmed(2, 70, 10, "right front leg");
   set_hitloc_unarmed(3, 70, 10, "left front leg");
   set_hitloc_unarmed(4, 100, 45, "chest");
   set_hitloc_unarmed(5, 70, 20, "right middle leg");
   set_hitloc_unarmed(6, 70, 20, "left middle leg");
   add_prop(LIVE_I_SEE_DARK, 1000);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   add_prop(LIVE_I_QUICKNESS, 100);
   add_prop(CONT_I_VOLUME,3000000);
   add_prop(CONT_I_WEIGHT,3000000);
   trig_new("%w 'tries' 'to' 'go' %s","react_attack");
}
int
special_attack(object enemy)
{
   int attacktype, i, j, k, penet, poisoned, poisoned_before;
   mixed* hitresult;
   string how;
   object me, *arr, *ob, poison;
   me = this_object();
   attacktype = random(5);
   if (attacktype == 1)
      {
      hitresult = enemy->hit_me(600 + random(400), W_BLUDGEON, me, -1);
      how = " but are uninjured";
      if(hitresult[0] > 0)
         if(hitresult[0] > 5)
         how = " and are slightly bruised";
      if(hitresult[0] > 10)
         how = " and are slow in standing";
      if(hitresult[0] > 15)
         how = " and are severely bruised";
      if(hitresult[0] > 20)
         how = " and are brutally hurt";
      me-> catch_msg("You smash your enemy into the wall!\n" +
         capitalize(enemy->query_pronoun()) + "is thrown violently against the wall" +
         how + ".\n");
      enemy-> catch_msg(QCTNAME(me) + " knocks you into the wall!\n" +
         "You are thrown against the wall" + how + ".\n");
      tell_watcher(QCTNAME(me) + " hammers " + QCTNAME(enemy) +  
         " into the wall!\n",enemy);
      if(enemy->query_hp() <=0)
         enemy->do_die(me);
      return 1;
   }
   if (attacktype == 3)
      {
      j = random(2);
      if (j == 0)
         {
         
         penet = 250 + random(200);
         
         hitresult = enemy->hit_me(penet, W_IMPALE, me, -1);
         
         how = "not harmed";
         if (hitresult[0] > 0)
            {
            poisoned = 1;
            how = "barely hurt";
          }
         if (hitresult[0] > 10)
            how = "slightly hurt";
         if (hitresult[0] > 20)
            how = "hurt";
         if (hitresult[0] > 30)
            how = "hurt quite badly";
         if (hitresult[0] > 40)
            how = "hurt quite badly";
         if (hitresult[0] > 50)
            how = "hurt very badly";
         if (hitresult[0] > 60)
            how = "utterly devastated";
         
         if (poisoned == 1)
            {
            arr = all_inventory(enemy);
            poisoned_before = 0;
            for (k = 0; k < sizeof(arr); k++)
            {
               if (function_exists("create_object", arr[k]) == "/std/poison_effect")
                  poisoned_before = 1;
             }
            if (poisoned_before == 0)
               {
               seteuid(geteuid(this_object()));
               poison = clone_object("/std/poison_effect");
               poison->move(enemy);
               poison->set_time(1000);
               poison->set_interval(10);
               poison->set_strength(60);
               poison->start_poison();
               
               poisoned = 0;
             }
          }
         enemy->catch_msg("You were " + how + " by the spider's mandibles!\n");
         tell_watcher(QCTNAME(enemy) + " is " + how + " by the spider's mandibles!\n", ob[i]);
         if (enemy->query_hp() <= 0)
            enemy->do_die(me);
         return 1;
       }
      enemy->catch_msg("You were missed by the spider's mandibles!\n");
      tell_watcher(QCTNAME(enemy) + " is missed by the spider's bite.\n");
      return 1;
   }
   if (attacktype == 5)
      
   {
      if (heal == 5)
         {
         return 0;
       }
      heal += 1;
      write("The huge spider glows brighter for a moment!\n"+
         "The huge spider seems more healthy!\n");
      say("The huge spider glows brighter for a moment!\n"+
         "The huge spider seems more healthy!\n");
      me->heal_hp(1500);
      return 1;
   }
   
   return 0;
}
int
react_attack(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(1.0,0.0,"return_attack",who);
      return 1;
   }
}
void
return_attack(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("emote leaps to the attack!");
      command("kill " + lower_case(obj->query_real_name()));
   }
}
