/*
**   ARGOS - Metro - Amphitheatre Entrance
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
   for (i=0; i<NUM; i++) make_thespian(i);
}
 
void create_room() {
   set_short("Amphitheatre of Argos");
   set_long(
       "You are standing on the slope of the grassy area inside the "+
       "Amphitheatre where patrons sit to watch the various productions. "+
       "The stage sits down the slope to the east in the 'valley' of "+
       "the area. Not much here except the grass. You can walk back "+
       "toward the entrance to the north.\n");
 
   add_item("stage",
       "It is a quarter-circular stage made of marble fitting "+
       "perfectly in the southeastern corner of the Amphitheatre "+
       "of the same shape. You can't get to it from here, as it "+
       "rises above the ground which slopes down from here to the "+
       "base of the stage.\n");
   add_item(({"seats","seating area"}),
       "Nothing more than the gentle slope of the ground, the "+
       "seating area is really anywhere one would want to sit. "+
       "It curves around the outter edge to the north.\n");
   add_item("ground",
       "It is a grassy area which slopes down toward the stage "+
       "to the east, obviously hollowed out so that a good "+
       "view of the stage can be had anywhere within the columns.\n");
   add_item("grass","It's just grass.\n");
   add_item("entrance","It is to the north.\n");
   add_item(({"Amphitheatre","amphitheatre"}),
       "It is a grassy outdoor area, sloping toward the east, "+
       "where dramatic and comic "+
       "theatrical presentations are made. It is in the shape of "+
       "a quarter circle, walled by a straight line of columns on "+
       "the south and east, and a curved line on the northwest. "+
       "The stage area is in the southeastern corner, high enough "+
       "above the crater-like area to be inaccessible from here.\n");
   add_item("columns",
       "The columns are set at regular intervals around the Amphitheatre, "+
       "rising high into the air, their capitols sculpted with masks "+
       "commonly worn by actors.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"amph1",   "north",0);
   reset_room();
}
