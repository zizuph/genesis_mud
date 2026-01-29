//
// NPC teaming code
//
// This code allows NPCs who are attacked to get help from NPCs on
// their team. It is called whenever the NPC is attacked, checks all
// objects in the room to see if they are a potential team member,
// then calls attack_object against the attacker.
//
// ATTACK_TEAM is a string property with the name of the team
// ATTACK_PASSIVE is an integer property, 1=Passive, 0=not
//
//
// History
// Date     Coder       Action
// -------- ----------- ---------------------------------------
// 1/12/95  Zima        Created
// 2/18/95  Zima        - add support for passive team member (ie:
//                        I won't help my team, but they should help me)
//                      - do not look for team members if I have no
//                        ATTACK_TEAM property.
// 6/10/98  Zima        - recoded as an inheritable object
//
inherit  "/std/monster";
#include "/d/Khalakhor/sys/defs.h"
#include "teamsupt.h"
#include <macros.h>
#include <filter_funs.h>
 
void attacked_by(object Enemy)
   {
   string MyTeamId = (TO->query_prop(ATTACK_TEAM));
   object TR       = ENV(TO);
   object *inv     = (FILTER_PRESENT_LIVE(all_inventory(TR))) - ({TO});
   int    i;
 
   // if enemy gone or i'm not on a team, nothing to do
   if (!(objectp(Enemy)&&stringp(MyTeamId))) return;
 
   // do normal attacked_by
   ::attacked_by(Enemy);
 
   // check living in room. If on our team, call attacker
   for (i=0; i<sizeof(inv); i++)
      {
      if (((inv[i]->query_prop(ATTACK_TEAM)) == MyTeamId) /* same team */
         && (!(inv[i]->query_prop(ATTACK_PASSIVE))) &&    /* !passive  */
         (!(inv[i]->query_attack())))                     /* !fighting */
            inv[i]->command("$kill " + OB_NAME(Enemy));
      }
   }
