/* Dragon by percy*/

#include "/d/Krynn/xak/xlocal.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <poison_types.h>

inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */

inherit "/std/act/domove"; /* Include this if you want the creature to move */
   inherit "/std/act/action"; /* Include this if you want your creature to act */
   inherit "/std/act/attack";

void
create_creature()
{
   int i;
   
   set_name("Drivak");
   set_short("giant scorpion");
   set_race_name("scorpion");
   set_long("A large scorpion. It's hard chitinous body looks very powerful.\n");
   set_adj("giant");
   
   for (i = 0; i < 6; i++)
   set_base_stat(i, 60 + random(8));
   
   set_hp(query_max_hp());
   
   set_skill(SS_DEFENCE, 40);
   
   set_alignment(-200);
   
   set_attack_unarmed(0, 60, 20, W_SLASH,  60, "left pincer");
   set_attack_unarmed(1, 60, 20, W_SLASH,  60, "right pincer");
   
   
   set_hitloc_unarmed(0, 70, 20, "head");
   set_hitloc_unarmed(1, 80, 50, "body");
   set_hitloc_unarmed(2, 70, 30, "tail");
   set_aggressive(1);
   
   
   add_prop(CONT_I_VOLUME, 267900);
   add_prop(CONT_I_WEIGHT, 278400);
}

tell_watcher(string str, object enemy)
{
   object me,*ob;
   int i;
   
   me = this_object();
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i = 0; i < sizeof(ob); i++)
   if (ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
}

int
special_attack(object enemy)
{
   
   int attacktype, i, j, k, penet, poisoned, poisoned_before;
   mixed* hitresult;
   string how;
   object me, *arr, *ob, poison;
   me = this_object();
   attacktype = random(3);
   if (attacktype == 0)
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
         enemy->catch_msg("You were " + how + " by the scorpions tail!\n");
         tell_watcher(QCTNAME(enemy) + " is " + how + 
		      " by the scorpions tail!\n");
         
         
         if (enemy->query_hp() <= 0)
            enemy->do_die(me);
         return 1;
       }
      enemy->catch_msg("You were missed by the scorpions tail!\n");
      tell_watcher(QCTNAME(enemy) + " is missed by the scorpions tail.\n");
      return 1;
   }
   return 0;
}
