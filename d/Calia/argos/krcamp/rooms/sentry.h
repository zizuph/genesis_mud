/* Sentry Code
** This code is used to create kretans and to check for the presence
** of these kretans (sentries) to block exits. check_blocked is invoked in
** the add_exit(PATH,DIRECTION,"@@check_blocked");
** Assumtions (to be declared in including file):
**   KRETAN_LIST   - list of strings with file names in NPC_DIR
**   ORIGIN_MSG    - when created, where the kretan "steps out from"
**
*/
#include "../kenemy.h"
 
object *kretan=allocate((sizeof(KRETAN_LIST)));
 
/* creates one kretan */
void make_kretan(int i) {
    if (kretan[i]) return;
    kretan[i]=clone_object(KRCAMP_DIR+"monsters/"+KRETAN_LIST[i]);
    kretan[i]->equip_me();
    kretan[i]->move(THIS);
    tell_room(THIS, QCNAME(kretan[i])+ORIGIN_MSG+"\n");
}
 
/* creates all kretans in room - normally called from reset_room() */
void make_kretans() {
   int i;
   for (i=0; i<(sizeof(KRETAN_LIST)); i++) make_kretan(i);
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
