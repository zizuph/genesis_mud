/*
**   ARGOS - Metro - Chariot Depot near Docks of Calia
**                   Connected at "roundabout" of Calia
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
 
int    query_chariot_signaled() { return chariot_signaled; }
int    query_chariot_here()     { return chariot_here; }
int    query_waiting()          { return waiting;      }
object pointer_me() { return (this_object()); }
object chariot_room() { return((IN_CHARIOT_ROOM)->pointer_me()); }
 
#include "depot_state.c"
#define  EXIT_ROOM "/d/Calia/mountain/road/road19" /* roundabout */
 
void reset_room() {
   if (attendant) return;
   attendant=clone_object(NPC_DIR+"dep_attendant");
   attendant->set_this_depot(DOCKS_ROOM);
   attendant->move(THIS);
   tell_room(THIS,QCTNAME(attendant)+" takes his post.\n");
}
 
void create_room() {
   set_short("On a pillared deck");
   set_long(
      "You are standing on a rectangular marble deck which is surrounded "+
      "by towering pillars on all four sides. A large "+
      "blue banner flutters in the wind from a pole in the center of "+
      "the deck, while a small plaque is fastened to the pole near "+
      "the bottom. There is an exit through the wall of pillars to "+
      "the northeast.\n");
 
   add_item(({"depot","deck"}),
      "It is a flat rectangular area paved with large square slabs "+
      "of smooth marble. This place serves as a depot for the "+
      "chariot transport between here and the Metropolis of Argos.\n");
   add_item(({"pillars","pillar"}),
      "The pillars line the edges of the rectangular area like "+
      "sentinels standing guard. Each is free-standing as there is "+
      "no ceiling supported by these marble trees. Each is topped "+
      "with a simple capitol with scrolled ends.\n");
   add_item("banner",
      "It is a large banner made of blue silk fluttering in the "+
      "gentle breeze. It bears the royal arms of Argos, a shield "+
      "emblazoned with a rampant winged horse surmounted by a crown "+
      "with three jewels.\n");
   add_item("pole",
      "The pole is made of iron and flies the banner high above your "+
      "head. A small plaque is bolted to it on the lower end.\n");
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
   add_item("plaque","It is bolted to the pole. It has writing on it.\n");
   add_cmd_item("plaque","read",
       "+------------------------------------+ \n"+
       "|       ARGOSIAN CHARIOT DEPOT       | \n"+
       "|------------------------------------| \n"+
       "|   Chariot transports arrive here   | \n"+
       "|      to take travelers to the      | \n"+
       "|        Metropolis of Argos         | \n"+
       "|                                    | \n"+
       "|             Cost - 1 sc            | \n"+
       "|              ........              | \n"+
       "|              ........              | \n"+
       "+------------------------------------+ \n"+
       "You notice some instructions written in fine print.\n");
 
   /* exits */
   add_exit(EXIT_ROOM,"northeast",0);
   reset_room();
}
#include "depot.inc"
