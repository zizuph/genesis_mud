/*
**  MCLUB - Memorial Shrine, Lower Level Entrance Room
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       4/7/95    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
create_room() {
   set_short("Anteroom of the conclave");
   set_long(
      "A natural spring bursts forth from behind the stone walls of "+
      "this below-ground anteroom, filling a small semi-circular pool "+
      "which seems to empty into the earth. Two candelabrum are placed "+
      "on either side of a doorway which leads to the north, their "+
      "white candles providing light for the dark chamber. A set of "+
      "steps lead up out of the chamber to the east.\n");
 
   add_item("spring",
      "The underground spring is a natural source of water which spills "+
      "through the stone walls of the anteroom on the south side. The "+
      "spring water enters the chamber near its top, making a small "+
      "waterfall to the hand made pool below.\n");
   add_item("conclave","It is the lower level of the shrine.\n");
   add_item("water",
      "It gushes from the earth from behind the wall near the ceiling, "+
      "filling the pool with a crystal clear bath.\n");
   add_item(({"anteroom","chamber","wall","walls"}),
      "This chamber is an anteroom to the lower level of the stone "+
      "shrine, the cold wet walls made of stone set into the mud of "+
      "the hill inside of which this room rests.\n");
   add_item("pool",
      "It is a semicircular pool dug into the floor of the chamber. "+
      "On second notice, you believe the cavern of the pool may be "+
      "natural, but smooth stones have been placed in a semicircle "+
      "around the pools edge. The water in the pool looks clear and "+
      "pure.\n");
   add_item(({"candleabrum","candles"}),
      "Twelve white candles sit in each of the two candleabrum on "+
      "each side of the doorway, their flickering flames casting "+
      "strange shadows all about.\n");
   add_item("steps",
      "A set of simple wooden steps lead above ground to the east.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_exit(ROOM_DIR+"shconcon","north",0);
   add_exit(ROOM_DIR+"shbellt1","steps", "@@steps");
}
 
int steps() {
   write("You climb the steps upward.\n");
   return 0;
}
 
int bathe() {
   object TP=this_player();
   object TR=this_object();
   write("You bathe yourself in the purifying spring water of the pool.\n");
   tell_room(TR,QCTNAME(TP)+" bathes in the waters of the pool.\n",TP);
   return 1;
}
 
int drink(string Parms) {
   object TP=this_player();
   string *parm;
   int    i;
   int    OK=0;
   if (!(Parms)) return 0;
   parm=explode(Parms," ");
   for (i=0; i<sizeof(parm); i++)
      if ((parm[i]=="water")||(parm[i]=="pool")||(parm[i]=="spring"))
         OK = 1;
   if (OK) {
      write("You drink from the pure waters of the spring.\n");
      tell_room(this_object(),QCTNAME(TP)+
                " drinks from the pure waters of the spring.\n",TP);
      return 1;
   }
   return 0;
}
 
void init() {
   ::init();
   add_action("bathe","bathe");
   add_action("drink","drink");
}
