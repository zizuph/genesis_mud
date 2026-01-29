/* Satyr Forest, a Newbie area
**
** History
** Date        Coder       Action
** --------  ------------  ----------------------
** 2/18/95   Zima          Created
**/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"
#include "defs.h"
#define NumSatyrs 2
int    leg_here=1;
object *satyr=allocate(NumSatyrs);
void reset_room() {
    int i;
    leg_here=1;
    for (i=0; i<NumSatyrs; i++)
       if (!(satyr[i])) {
          satyr[i]=clone_object(NPC_DIR+"satyr");
          satyr[i]->equip_me();
          satyr[i]->move(THIS);
          tell_room(THIS, QCNAME(satyr[i])+" jumps from behind a tree.\n");
      }
}
 
/* room definition */
void create_room() {
   set_short("A dense forest");
   set_long(
       "A gentle breeze lightly sways the limbs of the tall maples and "+
       "oaks which surround you, the chatter of a squirrel or some other "+
       "animal scolding you drifts from above. The trees grow so closely "+
       "here, their bases so entangled with underbrush, that you "+
       "can not continue further in this direction.\n");
 
#include "sfordesc.ext"
   add_item(({"squirrel","animal"}),
           "You can't see it, but you can hear its aggravated tirade "+
           "coming at you from somewhere in the trees.\n");
   add_cmd_item("underbrush","search","@@do_search");
 
   /* exits */
   add_exit(ROOM_DIR+"sfor6", "southeast",0);
   set_alarm(7.0,0.0,"reset_room");
}
 
void find_leg(object TPlay) {
   object TRoom=this_object();
   object leg;
   int    awareness=TPlay->query_skill(SS_AWARENESS);
   if ((leg_here) && (awareness >= 3)) {
      write("You find a marble goat's leg in the underbrush!\n");
      tell_room(QCNAME(TPlay)+" finds something in the underbrush.\n");
      leg=clone_object(OBJ_DIR+"sforleg");
      leg->move(TPlay);
      leg_here=0;
   }
   else
      write("Your search reveals nothing special.\n");
}
 
int do_search() {
   object TPlay=this_player();
   object TRoom=this_object();
   write("You start to search the underbrush.\n");
   tell_room(TRoom,QCNAME(TPlay)+" starts to search the underbrush.\n",TPlay);
   set_alarm(8.0,0.0,"find_leg",TPlay);
   return 1;
}
