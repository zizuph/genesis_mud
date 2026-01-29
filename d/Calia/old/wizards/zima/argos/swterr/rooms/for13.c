/* Evil forest in the Southwestern Territory of Argos
**
** A cassock stolen by the woodsmen from the library/museum in the
** city is found here with 'search forest'. The player can return
** the cassock to solve a quest. The woodsmen, if present, will attack
** anyone who finds the cassock, and will not let them leave with it.
**
** History
** Date       Coder         Action
** --------  ------------  ----------------------------------------
** 1/12/93   Zima          Created
** 8/8/95    Zima          Update for quest
** 6/9/95    Maniac        bug, resets  and typo dealt with  
**
**/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include "/sys/ss_types.h"
#include <macros.h>
#include "defs.h"
#include METRO_TOURS_DEF
#define NUM_WOODSMEN 3
 
object *woodman=allocate(NUM_WOODSMEN);
int    CassockFound=0;
 
void make_monster(int i) {
    if (woodman[i]) return;
    woodman[i]=clone_object(NPC_DIR+"woodsman");
    woodman[i]->equip_me();
    woodman[i]->move(THIS);
    tell_room(THIS, QCTNAME(woodman[i])+" walks down the path.\n");
}
 
void reset_room() {
   int i;
   CassockFound=0;
   for (i=0; i<NUM_WOODSMEN; i++) 
        make_monster(i);
}
 
/* room definition */
void create_room() {
   set_short("A dark forest");
   set_long(
       "You walk to the end of a path through a dark forest.  Tall pines " +
       "surround you on all sides, the wind swiping their sharp needles " +
       "at your skin.  There are the remains of a small campfire here, " +
       "still smoldering, surrounded by small bones.  You wonder if the " +
       "ones who built this are still around.  The forest grows so thick " +
       "here that your only way out is to the north.\n");
 
    add_item(({"forest","trees"}), break_string(
        "Towering pine trees, their bark as black as night and their " +
        "dark-green needles sharp enough to cut.\n",70));
    add_item("campfire", "A small stack of smoldering charred sticks.\n");
    add_item("bones",
             "Small charred bones scattered about, some still with meat.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"for8","north","@@north");
    reset_room();
}
 
int 
north() {
   /* if the player has the stolen cassock and woodsmen here, don't */
   /* let player leave                                              */
   object Tp=this_player();
   object Tr=this_object();
   object *ObList;
   int    i,GotIt,Stopped;
 
   /* if cassock hidden or no woodsmen here, let player leave */
   if (!(CassockFound)) return 0;
   if (!(present("woodsman",Tr))) return 0;
 
   /* check deep inventory of player to see if he/she has the cassock */
   GotIt=0;
   ObList=deep_inventory(Tp);
   for (i=0; i<sizeof(ObList); i++) if (ObList[i]->id(STOLEN_CASSOCK)) GotIt=1;
 
   if (!(GotIt)) return 0; /* let player go if he don't got it */
 
   /* player has cassock and woodsmen not happy about it */
   Stopped=0;
   for (i=0; i<NUM_WOODSMEN; i++)
      if (objectp(woodman[i]) && present(woodman[i],Tr)) {
         if (!(Stopped)) {
            Tp->catch_msg(QCTNAME(woodman[i])+" blocks your path.\n");
            tell_room(Tr,QCTNAME(woodman[i])+" stops "+QCTNAME(Tp)+
                      " from leaving.\n",Tp);
            Stopped=1;
         }
         if ((woodman[i]->query_attack())!=Tp) { /* not already fighting */
            Tp->catch_msg(QCTNAME(woodman[i])+" attacks you!\n");
            tell_room(Tr,QCTNAME(woodman[i])+" attacks "+QCTNAME(Tp)+"!\n",Tp);
            woodman[i]->attack_object(Tp);
         }
         woodman[i]->command("shout Drop the cassock or I'll kill you!");
      }
 
   return Stopped;
}
 
void 
find_cassock(object Tp) {
   object Tr=this_object();
   object cassock;
   int    awareness=Tp->query_skill(SS_AWARENESS);
   int prop=Tp->query_prop(ARGOS_TOUR_PROP);
 
   if (objectp(Tp) && present(Tp, this_object())) {
      if ((!(CassockFound))&&(awareness>=CASSOCK_QUEST_AWARENESS)&&
             (prop==ON_CASSOCK_QUEST)) {
          cassock=clone_object(ARMOUR_DIR+"cassock");
          Tp->catch_msg("You find a white cassock in the forest.\n");
          tell_room(Tr,QCTNAME(Tp)+" finds something in the forest.\n",Tp);
          cassock->move(Tp);
          CassockFound=1;
       }
       else
          write("Your search reveals nothing special.\n");
   }
}
 
int 
do_search(string Parms) {
   object Tp=this_player();
   object TRoom=this_object();
   string *Parm;
 
   /* take care of searching the forest only */
   if (!(Parms)) return 0;
   Parm=explode(Parms," ");
   if (member_array("forest",Parm)==-1) return 0;
 
   write("You start to search the forest.\n");
   tell_room(TRoom,QCTNAME(Tp)+" starts to search the forest.\n",Tp);
   set_alarm(8.0,0.0,"find_cassock",Tp);
   return 1;
}
 
void init() {
   ::init();
   add_action("do_search","search");
}
