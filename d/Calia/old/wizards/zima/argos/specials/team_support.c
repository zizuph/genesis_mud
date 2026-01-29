/*
** NPC teaming code
**
** This code allows NPCs who are attacked to get help from NPCs on
** their team. It is called whenever the NPC is attacked, checks all
** objects in the room to see if they are a potential team member,
** then calls attack_object against the attacker.
**
** ARGOS_ATTACK_TEAM is a string property with the name of the team
** ARGOS_ATTACK_PASSIVE is an integer property, 1=Passive, 0=not
**
**
** History
** Date     Coder       Action
** -------- ----------- ---------------------------------------
** 1/12/95  Zima        Created
** 2/18/95  Zima        - add support for passive team member (ie:
**                        I won't help my team, but they should help me)
**                      - do not look for team members if I have no
**                        ATTACK_TEAM property.
** 1/30/97  Zima        Converted to inheritable file
**/
/* #define ARGOS_ATTACK_TEAM    "_zimas_attack_team_prop" */
/* #define ARGOS_ATTACK_PASSIVE "_zimas_attack_passive_prop"     */
#include <macros.h>
#include "defs.h"
 
void attacked_by(object Enemy) {
   object TObj=this_object();
   string MyTeamId=(TObj->query_prop(ARGOS_ATTACK_TEAM));
   object TRoom=environment(TObj);
   object *RoomInv=((all_inventory(TRoom)) - ({TObj}));
   int    NumObj=sizeof(RoomInv);
   int    i;
 
   if (!Enemy) return;
   ::attacked_by(Enemy);
 
   if (!(MyTeamId)) return; /* if not on team, no need to check for friends*/
   set_this_player(Enemy); /* for writes */
 
   /* check each object in room. If on our team, call attacker */
   for (i=0; i<NumObj; i++) {
      if (((RoomInv[i]->query_prop(ARGOS_ATTACK_TEAM)) == MyTeamId)
         && (!(RoomInv[i]->query_prop(ARGOS_ATTACK_PASSIVE))) &&
         (!(RoomInv[i]->query_attack()))) {                   /* !fighting */
            Enemy->catch_msg(QCTNAME(RoomInv[i])+" attacks you!\n");
            tell_room(TRoom,QCTNAME(RoomInv[i])+" attacks "+QCNAME(Enemy)
                            +"!\n",Enemy);
            RoomInv[i]->attack_object(Enemy);
         }
   }
}
