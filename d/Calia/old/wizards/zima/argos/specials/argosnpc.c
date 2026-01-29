/* Standard Argos NPC
**
** This code inherits the mudlib standard NPC object and "enhances" it
** with attack support, introduction response, and equiping.
**
** Date     Coder       Action
** -------- ----------- ---------------------------------------
** 2/1/97   Zima        Created
**/
/* #define ARGOS_ATTACK_TEAM    "_zimas_attack_team_prop" */
/* #define ARGOS_ATTACK_PASSIVE "_zimas_attack_passive_prop"     */
inherit "/std/monster";
#include <macros.h>
#include "defs.h"
string   *intro_list     = (({})); /* list of players who've introed   */
string   *intro_resp_cmd = (({})); /* list of my responses to an intro */
int      i_resp_intros   = 0;      /* do I resp. to intros?            */
string   equip_dir       = "";     /* base directory of equipment      */
string   *equip_list     = (({})); /* list of my equip, relative to dir*/
 
/*
** ATTACKED_BY()   [mask of mudlib function]
** When I'm attacked, get "friends" in the room to attack my attacker
*/
public void attacked_by(object Enemy) {
   object  TObj=this_object();
   string  MyTeamId=(TObj->query_prop(ARGOS_ATTACK_TEAM));
   object  TRoom;
   object  *RoomInv;
   int     NumObj,i;
 
   if (!Enemy) return;
   ::attacked_by(Enemy);
 
   if (!(MyTeamId)) return; /* if not on team, no friends to find */
   set_this_player(Enemy);  /* for writes */
   TRoom    = environment(TObj);
   RoomInv  = ((all_inventory(TRoom)) - ({TObj}));
   NumObj   = sizeof(RoomInv);
 
   /* check each object in room. If on our team, call attacker */
   for (i=0; i<NumObj; i++) {
      if (((RoomInv[i]->query_prop(ARGOS_ATTACK_TEAM)) == MyTeamId)
         && (!(RoomInv[i]->query_prop(ARGOS_ATTACK_PASS))) &&
         (!(RoomInv[i]->query_attack()))) {                   /* !fighting */
            Enemy->catch_msg(QCTNAME(RoomInv[i])+" attacks you!\n");
            tell_room(TRoom,QCTNAME(RoomInv[i])+" attacks "+QCNAME(Enemy)
                            +"!\n",Enemy);
            RoomInv[i]->attack_object(Enemy);
         }
   }
}
 
/*
** RESPONSE TO INTRO BY PLAYER FUNCTIONS
*/
/* if new met player, add name to list & return 1, else return 0 */
public int check_intro(string name) {
   if (member_array(name,intro_list)>-1) return 0;
   intro_list=intro_list + ({name});
   return 1;
}
 
/* issue list of commands */
public void respond_to_intro() {
   int i;
   for (i=0; i<sizeof(intro_resp_cmd); i++)
      this_object()->command(intro_resp_cmd[i]);
}
 
/* invoked when a living intros to me */
public void add_introduced(string name) {
   if (this_player()->query_npc()) return;   /* ignore other npcs       */
   if (!(i_resp_intros)) return;             /* I don't resp. to intros */
   if (check_intro(name))                    /* if not introed before   */
      set_alarm(2.0,0.0,"respond_to_intro"); /*    then resp to intro   */
}
 
/* invoked from npc create_monster; set the list of intro responses */
public void set_intro_resp(string *resp_cmds) {
   intro_resp_cmd = resp_cmds;
   i_resp_intros  = 1;
}
 
/*
** EQUIPING FUNCTIONS
*/
public void set_equip(string *list)      { equip_list = list; }
public void set_equip_dir(string theDir) { equip_dir = theDir; }
public void equip_me() {
   object Tobj=this_object();
   int i;
   for (i=0; i<sizeof(equip_list); i++)
      (clone_object((equip_dir+(equip_list[i]))))->move(Tobj);
   command("wear all");
   command("wield all");
}
