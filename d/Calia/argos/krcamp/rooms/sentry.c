/* Sentry Code
** This code is used to create kretans and to check for the presence
** of these kretans (sentries) to block exits. check_blocked is invoked in
** the add_exit(PATH,DIRECTION,"@@check_blocked");
**
** Use:
** Invoke the following in create_room()
** - set_kretan_list(({"warrior/warrior1","dir/npcX","etc"}));
** - set_kretan_origin(" jumps out of the woods");
** Invoke the following in reset_room()
** - make_kretans();
** Invoke the following in an add exit
** - add_exit(PATH,DIRECTION,"@@check_blocked");
**
** Date      Coder        Actions
** --------  -----------  ---------------------------------------
** 1996      Zima         Created as includable .h
** 1/25/97   Zima         recoded as inheritable .c
**
*/
#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "../kenemy.h";
#define MAX_KRETANS 7
 
int    NumKretans=0;                      /* # kretans in this room */
string *KretanList;                       /* list of NPC path names */
object *kretan=allocate(MAX_KRETANS);     /* list of Kretan objects */
string KretanOrigMsg=" arrives";          /* default origin message */
 
/* allows inheriting room to set the list of Kretans */
void set_kretan_list(string *list) {
   NumKretans=sizeof(list);
   if (NumKretans>MAX_KRETANS) NumKretans=MAX_KRETANS;
   KretanList=list;
}
 
/* allows inheriting room to set the origin/arrival message */
void set_kretan_origin(string orig) {
   KretanOrigMsg=orig;
}
 
/* creates one kretan */
void make_kretan(int i) {
    if (kretan[i]) return;
    kretan[i]=clone_object(KRCAMP_DIR+"monsters/"+KretanList[i]);
    kretan[i]->equip_me();
    kretan[i]->move(THIS);
    tell_room(THIS, QCNAME(kretan[i])+KretanOrigMsg+".\n");
}
 
/* creates all kretans in room - normally called from reset_room() */
void make_kretans() {
   int i;
   for (i=0; i<NumKretans; i++) make_kretan(i);
}
 
/* check_blocked: returns 1 if kretan here to guard exit and player is   */
/*                not disguised as a Kretan (see kenemy.h) and Kretan    */
/*                can see the player, 0 otherwise.                       */
/*                Called from add_exit() in rooms with guarded exits     */
int check_blocked() {
   int    i;
   object To=this_object();
   object Tp=this_player();
   object guard=present("kretan",To);
 
   /* see if there is a Kretan here to guard the exit */
   if (!guard) return 0;
 
   /* if player is invisible, or Kretan can't see, let player pass */
   if (!((CAN_SEE(guard,Tp))&&(CAN_SEE_IN_ROOM(guard))))
      return 0;  /* guard can't see player */
 
    /* if player is disguised as a Kretan, guard lets him pass */
    if (!(kretan_enemy(Tp))) {
       guard->command("nod "+(Tp->query_name()));
       return 0;
    }
 
    /* a guard is here who can see that the player not disguised...block */
    Tp->catch_msg(QCTNAME(guard)+" blocks your way.\n");
    tell_room(To,QCTNAME(guard)+" blocks "+QCTNAME(TP)+
                 " from passing.\n",Tp);
    return 1;
}
