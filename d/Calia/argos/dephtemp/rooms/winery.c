/*
**  Temple of Dephonia, Winery.
**
**  The sacramental wine needed to do the Vision Quest is found here.
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/1/94    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "defs.h"
int      wine_here=1;
 
void reset_room() { wine_here=1; }
 
create_room() {
   set_short("Winery of the Temple of Dephonia");
   set_long(
      "This cramped rectangular chamber is the winery and brewery of "+
      "the temple. Long racks of bottles of retsina sit in rows crowded "+
      "across the chamber. There are several large jugs sitting along "+
      "the west wall, and a simple table sits along the east. The "+
      "doorway leads south back to the kitchen.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("racks","They are tall wooden racks stocked with bottles "+
            "of retsina, the local wine. They almost reach the ceiling "+
            "and sit in long rows across the room.\n");
   add_item("retsina","Hundreds of bottles of retsina sit on the racks.\n");
   add_item("jugs","The jugs are filled with fermenting fluids.\n");
   add_item("table","@@exa_table");
   add_item(({"black wine","bottle of black wine","black bottle",
              "wine on table","wine from table","bottle of wine on table",
              "bottle of wine from table","wine"}),
              "@@exa_wine");
   add_cmd_item(({"black wine","bottle of black wine","black bottle",
              "wine on table","wine from table","bottle of wine on table",
              "bottle of wine from table","wine"}), ({"take","get"}),
              "@@take_wine");
 
   add_exit(ROOM_DIR+"kitchen","south",0);
   reset_room();
}
 
string exa_table() {
   string desc="It is a simple wooden table sitting next to the wall. ";
   if (wine_here) desc=desc+"There is a bottle of black wine sitting "+
                            "on it.\n";
   else           desc=desc+"\n";
   return desc;
}
string exa_wine() {
   if (wine_here) return "It is a bottle of black wine like none other in "+
                  "the room. It seems to have been set out for a "+
                  "special purpose.\n";
   else return "You find no particular bottle of wine.\n";
}
 
int take_wine() {
   object TPlay=this_player();
   object TRoom=environment(TPlay);
 
   if (wine_here)
      if (((TPlay->query_armour(A_BODY))->id(VDQ_ROBE))  && /* wears robe */
          ((TPlay->query_armour(A_NECK))->id(VDQ_MEDAL)))   /* wears medal*/
         {
         wine_here=0;
            set_alarm(1000.0,0.0,"reset_room");
            (clone_object(OBJ_DIR+"viswine"))->move(TPlay);
            write("You take the bottle of black wine from the table.\n");
            tell_room(TRoom,QCNAME(TPlay)+" takes the bottle of black "+
                      "wine from the table.\n",TPlay);
         }
      else write("It is reserved for ritualistic purposes. You decide "+
                 "you better leave it alone.\n");
   else write("You find no particular bottle of wine.\n");
   return 1;
}
