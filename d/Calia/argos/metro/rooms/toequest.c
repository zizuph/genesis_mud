/* Functions included by rooms involved in the Toe Quest
** Players must "rub toe of statue" of the statues of the nine
** monarchs of Argos. Each room with a statue should include this
** file and set the PropThisStatue variable via the given function.
**
** History:
** Date      Coder     Action
** -------- ---------- -------------------------------
** 8/5/95   Zima       Created
*/
#include <macros.h>
#include "../tours.h"
int ThisStatue=-1; /* to be initialized by each room via function */
 
/* each room in quest calls this function to id which statue here */
void toe_quest_set_statue_prop(int ThisProp) {
   /* used to init PropThisStatue */
   ThisStatue=ThisProp;
}
 
/* determines if all statues rubbed */
int AllRubbed(int *Prop) {
   int size=sizeof(Prop);
   int i;
   int done=1;
 
   for (i=0; i<size; i++)
      if (!(Prop[i])) done=0;
   return done;
}
 
int rub(string Parms) {
   object TPlay=this_player();
   object TRoom=this_object();
   string *Parm;
   int    toendx,statuendx,OK;
   int    *Prop=TPlay->query_prop(TOE_QUEST_PROP);
 
   if (!(Parms)) { write("Rub what?\n"); return 1; }
   Parm=explode(Parms," ");
   toendx=member_array("toe",Parm);
   statuendx=member_array("statue",Parm);
 
   OK=0;
   if (toendx==-1)
      if (statuendx==-1)
         write("Rub what?\n");
      else
         write("Rub what on statue?\n");
   else
      if (statuendx==-1)
         write("Rub toe on what?\n");
      else
         OK=1;
   if (!(OK)) return 1;
 
   write("You rub the toe of the statue.\n");
   tell_room(TRoom,QTNAME(TPlay)+" rubs the toe of the statue.\n",TPlay);
 
   if ((TPlay->query_prop(ARGOS_TOUR_PROP))==ON_TOE_QUEST) {
      if (Prop)
         if (Prop[ThisStatue]) /* already rubbed toe on this statue */
            write("You seem to have gotten all the luck you can here.\n");
         else {
            /* first time at this statue */
            Prop[ThisStatue]=1;
            TPlay->add_prop(TOE_QUEST_PROP,Prop);
            if (AllRubbed(Prop)) {
               write("You feel like this really must be your lucky day!\n");
               TPlay->add_prop(ARGOS_TOUR_PROP,TOE_QUEST_DONE);
               TPlay->remove_prop(TOE_QUEST_PROP);
               }
            else /* not done yet */
               write("You feel like this might be your lucky day!\n");
         }
      else {
         /* prop not here, so this is first statue rubbed */
         Prop=(({0,0,0,0,0,0,0,0,0})); /* 9 total statues */
         Prop[ThisStatue]=1;
         TPlay->add_prop(TOE_QUEST_PROP,Prop);
         write("You feel like this might be your lucky day!\n");
      }
   }
   return 1;
}
 
void init() {
   ::init();
   add_action("rub","rub");
}
