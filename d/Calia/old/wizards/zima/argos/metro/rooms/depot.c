/*
**   ARGOS - Metro - Strathmos, Chariot Depot (transport to Docks)
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/12/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "defs.h"
#include "chariot.h"
 
object chariot;
object attendant;
int    chariot_signaled=0;
int    chariot_here=0;
int    waiting=0;
 
int query_chariot_signaled() { return chariot_signaled; }
int query_chariot_here()     { return chariot_here;     }
int query_waiting()          { return waiting;          }
object pointer_me()   { return (this_object()); }
object chariot_room() { return ((OUT_CHARIOT_ROOM)->pointer_me()); }
 
#include "depot_state.c"
 
void reset_room() {
   if (attendant) return;
   attendant=clone_object(NPC_DIR+"dep_attendant");
   attendant->set_this_depot(DEPOT_ROOM);
   attendant->move(THIS);
   tell_room(THIS,QCTNAME(attendant)+" takes his post.\n");
}
 
void create_room() {
   set_short("The Strathmos");
   set_long(
       "You are standing in an area enclosed by a high iron fence, "+
       "marble benches lining the perimeter. This is the Strathmos "+
       "of Argos, the depot where chariots arrive to take travellors "+
       "out of the valley to the docks at the sea far to the west. "+
       "A plaque is bolted to the posts of the fence, through which "+
       "arched gates "+
       "lead west and south into the streets of the city, while another "+
       "leads east to the Aeropagus.\n");
 
   add_item(({"strathmos","Strathmos","depot"}),
       "It is the depot where chariot transports arrive. It is walled "+
       "by a high iron fence.\n");
   add_item("fence",
       "The iron fence is made of tall poles with spikes on them, "+
       "making the area seem almost like an open-aired prison.\n");
   add_item("benches",
       "Simple flat marble benches line the perimeter of the area "+
       "next to the fence.\n");
   add_item(({"gate","gates"}),
       "Arched gates in the fence allow access to the streets of the "+
       "city to the west and south, and to the Aeropagus to the east.\n");
   add_item(({"aeropagus","Aeropagus"}),
       "It is the commons area of the city. A gate leads east into it.\n");
   add_item(({"instructions","fine print","print"}),
       "Some instructions are written in fine print on the bottom of the "+
       "plaque. Perhaps you can read them.\n");
   add_cmd_item(({"instructions","fine print","print"}),"read",
      "----------------------------------\n"+
      "   Instructions for chariot use   \n"+
      "----------------------------------\n"+
      "To use the chariot, do:           \n"+
      "'ask attendant to summon chariot' \n"+
      "Wait for the chariot to arrive    \n"+
      "'pay attendant' the fee           \n"+
      "'board' the chariot               \n"+
      "When you are ready to leave do    \n"+
      "   'crack whip'.                  \n");
   add_item("plaque","It is bolted to the fence. It has writing on it.\n");
   add_cmd_item("plaque","read",
       "+------------------------------------+ \n"+
       "|   STRATHMOS OF THE CITY OF ARGOS   | \n"+
       "|------------------------------------| \n"+
       "|   Chariot transports arrive here   | \n"+
       "|      to take travelers to the      | \n"+
       "|           Docks of Calia           | \n"+
       "|                                    | \n"+
       "|             Cost - 1 sc            | \n"+
       "|              ........              | \n"+
       "|              ........              | \n"+
       "+------------------------------------+ \n"+
       "You notice some instructions written in fine print.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"droad10","west",0);
   add_exit(ROOM_DIR+"croad11","south",0);
   add_exit(ROOM_DIR+"aeropagus","east",0);
   reset_room();
}
#include "depot.inc"
