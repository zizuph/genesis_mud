
/* 
   Remote desc of a room. 

   !! This code is adapted thanks to Plugh's ctower torque of Emerald,  
   !! with permission from Rohim.  

   Adapted by Maniac, 20/4/96 
   Modified, Maniac, 27/9/96, 9/11/96
*/

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <state_desc.h>
#include <filter_funs.h>
#include <composite.h>
#include <state_desc.h>
#include <living_desc.h>
#include <options.h>


string
contents_desc(object env)
{
     object *items, *dead, *live, *ctants1, *ctants2; 
     mixed attackers; 
     object enemy, tp; 
     string res, verb;
     int i, size, index;

     res = "";
     tp = this_player(); 

     if (!objectp(env) || !env->query_prop(ROOM_I_IS))
         return 0;
      
     items = FILTER_CAN_SEE(all_inventory(env), tp);
     if (sizeof(items)) {
         if (sizeof(dead = FILTER_DEAD(items))) 
             res += (capitalize(COMPOSITE_DEAD(dead)) + ".\n");
    
         if (sizeof(live = FILTER_LIVE(items)))
             res += (capitalize(COMPOSITE_LIVE(live)) + ".\n");
      }

      ctants1 = ({ });
      ctants2 = ({ });
      attackers = ({ });
      i = -1;
      size = sizeof(live);

      while (++i < size) {
          if (enemy = live[i]->query_attack()) {
              if (member_array(live[i], ctants1) >= 0) {
                  // already taken care of!
                  continue;
               }

              if (enemy->query_attack() == live[i]) {
                  // describe two livings attacking each other
                  res += (live[i]->query_The_name(tp) +
                         " and " + enemy->query_the_name(tp) +
                         " are fighting each other.\n");       
                  ctants1 += ({ enemy });
                  continue;
               }

              if (sizeof(ctants2) &&
                  (index = member_array(enemy, ctants2)) >= 0) {
                   // group all attackers of same living
                   attackers[index] += ({ live[i] });
                   continue;
              }

              attackers += ({ ({ live[i] }) });
              ctants2 += ({ enemy });
         }
    }

    i = -1;
    size = sizeof(ctants2);
    while (++i < size) {
        verb = (sizeof(attackers[i]) == 1 ? " is " : " are ");
        res += (COMPOSITE_LIVE(attackers[i]) + verb + "fighting " + 
                ctants2[i]->query_the_name(tp) + ".\n");
     }

    return res;
}


varargs string
room_desc(object env, int always_long)
{
     object tp;
     string tmp, rd, cond;

     tp = this_player(); 

     if (!objectp(env) || !env->query_prop(ROOM_I_IS)) 
         return 0;

     if (env->query_prop(OBJ_I_LIGHT) < (tp->query_prop(LIVE_I_SEE_DARK)+1)) 
        if (!stringp(tmp = env->query_prop(ROOM_S_DARK_LONG))) 
            return LD_DARK_LONG;
        else 
            return tmp;

     if (tp->query_option(OPT_BRIEF) && !always_long)  
        rd = (env->short(tp) + ".\n" + env->exits_description()); 
     else
        rd = env->long(0, tp); 

     cond = contents_desc(env);  

     return (rd + cond); 
}

