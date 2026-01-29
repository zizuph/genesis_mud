/*
** ARGOS - City - Rental Room in the Inn of Argos - Temp Start Loc
**
** History:
** Date       Coder         Action
** -------- --------------- ---------------------------------
** 8/12/95  Zima            Created. Player must rent room in inn.c t
**                          to start here.
**/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("Theros Inn");
   set_long(
      "You are in a cozy room in Theros Inn in the city of Argos. "+
      "The room is furnished with a comfortable bed and a washstand. "+
      "A window on the west wall overlooks the street outside, while "+
      "a doorway leads north to the inn's kitchen.\n");
 
   add_item("bed",
      "It is a simple bed made of wood with a straw mattress, covered "+
      "with a wool blanket.\n");
   add_item("mattress","It is a straw mattress on the bed, very "+
      "comfortable.\n");
   add_item("blanket","It is a white wool blanket for whomever sleeps "+
      "here.\n");
   add_item(({"stand","washstand"}),
      "It is a tall stand made of wood with a bowl of water on it. "+
      "There is a card with an important note sitting on it also.\n");
   add_item("window",
      "It overlooks busy Deuteron road. You can see the Emporium "+
      "across the street.\n");
   add_item("bowl","It is full of water. Perhaps you could wash "+
            "your face.\n");
   add_item("card","It has important instructions on in. You should "+
            "read them.\n");
   add_cmd_item("card","read","@@read_card");
 
   /* room properties */
   add_prop(ROOM_I_INSIDE,1);
 
   /* exits */
   add_exit(ROOM_DIR+"inn","north",0);
}
 
string read_card() {
   return (
   "You may start in this room the next time you login. \n"+
   "To rent the room, do the following:                 \n"+
   " - goto the kitchen and 'rent room'                 \n"+
   " - come back in here and do 'start here'            \n"+
   "The rental is good for only one night, so if you    \n"+
   "don't rent the room when you login next time, you   \n"+
   "start in your regular home the following login.\n");
}
 
int start (string where) {
   int    rc;
   object Tp=this_player();
 
   if (where != "here") return 0;
   if (Tp->query_prop(RENTED_INN_ROOM)) {
      rc = Tp->set_temp_start_location(ROOM_DIR+"inn2");
      if (rc) {
         write("When you rise next, it shall be in this cozy place.\n");
      }
      else {
         write("Sorry...there is a problem with starting here. "+
               "Please log a bug report.\n");
      }
   }
   else write("You need to rent the room in the kitchen first.\n");
   return 1;
}
 
int wash() {
   write("You wash yourself in the water of the bowl.\n");
   tell_room(this_object(),QCTNAME(this_player())+" washes in the "+
             "water of the bowl.\n");
}
 
void init() {
   ::init();
   add_action("start","start");
   add_action("wash","wash");
}
