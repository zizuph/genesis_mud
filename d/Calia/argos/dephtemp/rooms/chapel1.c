/*
**  Temple of Dephonia - Chapel
**
** Vision Quest: This is where the player receives a vision of a
**    particular event in the history of the Order. He does this
**    by being poisoned with a VDQ_POISON object (see rooms/talis)
**    and by praying here.
**    He then searches the temple to find the tapestry with the same
**    scene as he gets here, reads the particular prayer for that
**    scene, and returns here to pray the words of the prayer. He
**    then receives an invisible "blessing" object needed to do the
**    rest of the quest.
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/5/95    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "defs.h"
#include "vqscenes.h"
#include "chapel.ext" /* extension to this file */
 
create_room() {
   set_short("The Chapel  of the Temple of Dephonia");
   set_long(
      "You step into a dark triangular chamber which serves as a "+
      "chapel in the temple. In the center of the room is an altar "+
      "upon which rests a short pillar candle, its small flame giving "+
      "the only light to this place of prayer. There is a short bench "+
      "sitting in front of the altar used for kneeling. You feel as " +
      "if the room is full of spirits.\n");
 
   add_item("altar", "It is a triangular altar made of carved mohagany, "+
            "obviously very old. A single candle sits on top of the "+
            "altar and a short bench sits before it.\n");
   add_item("candle","It is a red candle, a thick pillar of wax "+
            "designed to burn for a long time. Its flame gives a "+
            "somber light to the chapel.\n");
   add_item("walls","The three walls are made of marble as black "+
            "as the darkest night. A crescent moon has "+
            "been set into each of the three walls.\n");
   add_item("bench","It is a short mohagany bench only a few inches "+
            "above the floor. The faithful kneel on the bench before "+
            "beginning their prayers.\n");
 
   add_prop(ROOM_I_INSIDE,1);
   add_exit(ROOM_DIR+"corr17","west","@@west");
}
 
void init() {
   ::init();
   add_action("kneel","kneel"); /* kneel at the altar */
   add_action("rise","rise");   /* rise from kneeling */
   add_action("pray","pray");   /* prayer commands    */
}
 
int west() {
   if (present(VDQ_KNEELING,this_player())) {
      write("You must rise first.\n");
      return 1;
   }
   return 0;
}
 
int kneel() {
   object TPlay    = this_player();
   object kneeling = present(VDQ_KNEELING,TPlay);
 
   if (kneeling)
      write("You already kneel before the altar.\n");
   else {
      kneeling=clone_object(OBJ_DIR+"viskneel");
      kneeling->move(TPlay);
      write("You kneel reverently before the altar.\n");
      tell_room(this_object(),QCNAME(TPlay)+
                " kneels reverently before the altar.\n",TPlay);
   }
   return 1;
}
 
int rise() {
   object TPlay    = this_player();
   object kneeling = present(VDQ_KNEELING,TPlay);
 
   if (kneeling) {
      kneeling->remove_object();
      write("You rise from your meditation.\n");
      tell_room(environment(TPlay), QCNAME(TPlay)+
                " rises from meditation.\n",TPlay);
      }
   else
      write("But you aren't kneeling!\n");
   return 1;
}
 
void unknown_prayer(object TPlay) {
   /* assumes player wearing robe/medallion, kneeling, and is poisoned */
   set_this_player(TPlay);
   if (present(VDQ_REVELATION,TPlay)) /* has received revelation */
      write("You hear spirits whisper: Pray the ancient words in honour "+
            "of that which was revealed to you, and you shall be blessed.\n");
   else
      write("You hear spirits whisper: For what do you pray, aspirant?\n");
}
 
int pray(string parm) {
   object TPlay    = this_player();
   object poison   = present(VDQ_POISON,TPlay);
   object kneeling = present(VDQ_KNEELING,TPlay);
   object robe     = ((TPlay->query_armour(A_BODY))->id(VDQ_ROBE));
   object medal    = ((TPlay->query_armour(A_NECK))->id(VDQ_MEDAL));
   object TRoom    = this_object();
   int    PrayerNum;
   int    i;
 
   if (kneeling) {
         write("You pray reverently before the altar.\n");
         tell_room(TRoom,QCNAME(TPlay)+" prays reverently before the altar.\n",
                   TPlay);
 
         if ((medal)&&(robe))
            if (poison) {
               /* switch/case won't work with variable case labels :( */
               if (parm=="for revelation")
                  set_alarm(7.0,0.0,"show_scene",TPlay,TRoom,1);
               else {
                  PrayerNum=0;
                  for (i=1; i<sizeof(vq_prayer); i++)
                     if (parm==vq_prayer[i]) {
                        PrayerNum=i;
                        i=(sizeof(vq_prayer))+1; /* stop search */
                     }
                  if (PrayerNum)
                     honour_prayer(TPlay,PrayerNum);
                  else
                     unknown_prayer(TPlay);
                  }
               } /* end if poisoned */
            else /* kneeling and dressed but not poisoned */
               write("You seem unable to commune with the spirits.\n");
         else /* kneeling but not dressed */
            write("Your mind is too clear to commune with the spirits.\n");
      }
   else /* not kneeling */
         write("Your irreverent invocation goes unheeded.\n");
   return 1;
} /* pray() */
