inherit "/std/creature";
inherit "/std/combat/unarmed.c";
inherit "/std/act/attack.c";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <const.h>
#define A_MANDIBLE  0
#define A_RLEG1 1
#define A_LLEG1 2
#define A_RLEG2 3
#define A_LLEG2 4
#define H_HEAD 0
#define H_BODY 1
#define H_RLEG1 2
#define H_LLEG1 3
#define H_RLEG2 4
#define H_LLEG2 5

void
create_creature()
{
   set_short("fierce thri-kreen");
   set_race_name("thri-kreen");
   set_adj("fierce");
   set_long("A seven foot tall insectoid, this creature has four arms "
	+"to wield weapons with, as well as four legs. Its head is "
	+"staring straight ahead, and a green viscous fluid is dripping "
	+"from its mouth. This is what appears to be a legendary "
	+"thri-kreen, or mantis warrior.\n");
   set_stats(({ 140, 160, 140, 75, 75, 100}));
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_AWARENESS,100);
   set_alignment(0);
   set_attack_unarmed(A_MANDIBLE, 70, 70, W_IMPALE, 30, "mandible");
   set_attack_unarmed(A_RLEG1, 55, 55, W_BLUDGEON, 25, "right front leg");
    set_attack_unarmed(A_LLEG1, 55, 55, W_BLUDGEON, 25, "left front leg");
   set_attack_unarmed(A_RLEG2, 55, 55, W_BLUDGEON, 10, "right middle leg");
   set_attack_unarmed(A_LLEG2, 55, 55, W_BLUDGEON, 10, "left middle leg");
   set_hitloc_unarmed(H_HEAD, ({39,39,39,39}), 15, "head");
   set_hitloc_unarmed(H_BODY, ({60,60,60,60}), 35, "body");
   set_hitloc_unarmed(H_RLEG1, ({40,40,40,40}), 13, "right front leg");
   set_hitloc_unarmed(H_LLEG1, ({40,40,40,40}), 13, "left front leg");
   set_hitloc_unarmed(H_RLEG2, ({40,40,40,40}), 12, "right middle leg");
    set_hitloc_unarmed(H_LLEG2, ({40,40,40,40}), 12, "left middle leg");
   add_prop(LIVE_I_SEE_DARK, 1000);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   add_prop(LIVE_I_QUICKNESS, 50);
   add_prop(CONT_I_VOLUME,3000);
   add_prop(CONT_I_WEIGHT,3000);
}
int
special_attack(object enemy)
{
   int attacktype, i, k, penet, poisoned, poisoned_before;
   mixed* hitresult;
   string how;
   object me, *arr, *ob, poison;
   me = this_object();

         if(random(6))  return 0;

	i = random(5);
      if (i == 0)
         {

         penet = 100 + random(200);

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
               if (function_exists("create_object", arr[k]) ==
"/std/poison_effect")
                  poisoned_before = 1;
             }
            if (poisoned_before == 0)
               {
               seteuid(geteuid(this_object()));
               poison = clone_object("/std/poison_effect");
               poison->move(enemy);
               poison->set_time(100);
               poison->set_interval(10);
               poison->set_strength(60);
               poison->start_poison();

               poisoned = 0;
             }
          }
     enemy->catch_msg("You were " + how + " by the thri-kreen's "
  +"mandibles!\n");
    tell_watcher(QCTNAME(enemy) + " is " + how + " by the "
   +"mandibles!\n", ob[i]);
         if (enemy->query_hp() <= 0)
            enemy->do_die(me);
         return 1;
       }
      enemy->catch_msg("You were missed by the thri-kreen's bites!\n");
      tell_watcher(QCTNAME(enemy) + " is missed by the thri-kreen's bite.\n");
      return 1;
   return 0;
}
