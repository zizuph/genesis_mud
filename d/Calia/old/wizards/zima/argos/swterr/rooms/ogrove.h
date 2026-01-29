/* PICK_OLIVES function
**
** Allows picking of olives from olive trees in Argos
** To be included by all rooms where function needed
** Note: NumOlives should be set to MAX_OLIVES in reset_room
**
** Date      Coder      Action
** --------- ---------- -----------------------------------
** 12/93     Zima       Created
** 8/24/95   Zima       Recoded to pick handfuls of olives instead
**                      of individual olives
**
*/
#define MAX_OLIVES 3
int NumOlives;   /* number of handfuls of olives available */
 
/* Allows the player to pick olives from the tree */
int pick_olives(string Parms) {
   object Tp=this_player();
   object Tr=this_object();
   object olives;
   string *Parm;
 
   /* must specify to pick olives */
   if (!(Parms)) return 0;
   Parm=explode(Parms," ");
   if ((member_array("olive",Parm)==-1) && (member_array("olives",Parm)==-1))
      return 0;
 
   if (NumOlives < 1) {
      write("All the olives you can reach have been picked.\n");
      return 1;
   }
 
   write("You pick a handful of olives from the tree.\n");
   tell_room(Tr,QCTNAME(Tp)+" picks a handful of olives from the tree.\n",Tp);
   olives=clone_object(OBJ_DIR+"olives");
   olives->move(Tp);
   NumOlives=NumOlives-1;
   return 1;
}
 
void init() {
   ::init();
   add_action("pick_olives","pick");
}
