/*
**   ARGOS - Metro - Amphitheatre - Stage
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   1/30/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define NUM 2
object *thespian=allocate(NUM);
 
void make_thespian(int i) {
    if (thespian[i]) return;
    thespian[i]=clone_object(NPC_DIR+"thesp_app"); /* apprentices */
    thespian[i]->equip_me();
    thespian[i]->move(THIS);
    tell_room(THIS, QCTNAME(thespian[i])+" walks down the slope.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) set_alarm(1.0,0.0,"make_thespian",i);
}
 
void create_room() {
   set_short("Amphitheatre of Argos");
   set_long(
       "You are standing on the stage of the Amphitheatre of Argos, "+
       "a quartercircular structure which rises from the southeastern "+
       "corner of the shallow valley made for the Amphitheatre. The "+
       "seating areas rise along the slope to the north, northwest "+
       "and west. The only access to the stage is through the doorway "+
       "to the south.\n");
 
   add_item("stage",
       "It is a quarter-circular stage made of marble fitting "+
       "perfectly in the southeastern corner of the Amphitheatre "+
       "of the same shape.\n");
   add_item(({"seats","seating area"}),
       "Nothing more than the gentle slope of the ground, the "+
       "seating area is really anywhere one would want to sit. It curves "+
       "around the outer edge from the west to the north.\n");
   add_item("ground",
       "It is a grassy area which slopes down toward the stage "+
       "to the south, obviously hollowed out so that a good "+
       "view of the stage can be had anywhere within the columns.\n");
   add_item("grass","It's just grass.\n");
   add_item("entrance","It is to the west.\n");
   add_item(({"Amphitheatre","amphitheatre"}),
       "It is a grassy outdoor area, sloping toward the stage, "+
       "where dramatic and comic "+
       "theatrical presentations are made. It is in the shape of "+
       "a quarter circle, walled by a straight line of columns on "+
       "the south and east, and a curved line on the northwest. "+
       "The stage area is in the southeastern corner.\n");
   add_item("columns",
       "The columns are set at regular intervals around the Amphitheatre, "+
       "rising high into the air, their capitols sculpted with masks "+
       "commonly worn by actors.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"thesp1","south",0);
   set_alarm(1.0,0.0,"reset_room");
}
