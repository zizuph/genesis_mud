/* Created by Macker 11/2/94 */
/* aurak code redone by Stevenson to conform with Olorin's method */
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"

inherit ICEINROOM;

int muppet_here = 0;
object aurak;

void reset_icewall_room() {
   if (!muppet_here) muppet_here = 1;
}

void create_icewall_room() {
   set_short("Trophy Room");
   set_long("This room's walls are covered with the heads of " +
      "many dead animals. There are also a few stuffed " +
      "animals on the floor in the corners of the room.\n");
   add_item(({"heads", "walls", "animal heads", "trophies"}),
      "The walls are covered with heads of many animals. " +
      "Griffons, bears, orcs, kender, goblins, " +
      "elves, humans, gnomes, dwarves, and hobbits " +
      "are just a few that catch your attention. There " +
      "are more animals on the floor in the corners of " +
      "the room if you care to look.\n");
   add_item(({"stuffed animals", "animals", "corners", "floor"}),
      "@@stuffed_animals@@");
   
   
   add_exit(ICE_CAST2_R+"hall5_2","east");
   
   reset_icewall_room();
}

string
stuffed_animals()
{
   if (!objectp(aurak) && muppet_here)
      {
      tell_room(TO,QCTNAME(TP)+" starts searching through the stuffed "
         + "animals and finds something.\n",TP);
      aurak = clone_object(SPLAINS_L + "aurak.c");
      aurak->set_color("white");
      aurak->move(TO);
      muppet_here = 0;
      set_alarm(1.0,0.0,"cackle",aurak);
      return("There are quite a few stuffed animals " +
         "here. Before you, you see a squirrel, a rat, " +
         "a wolf, a skunk, a draconian....." +
         "\n\nACK!\n\nThat's a real draconian!\n\n");
   }
   else
      return("There are quite a few stuffed animals " +
      "here. Before you, you see a squirrel, a rat, " +
      "a wolf, a skunk, and many more.\n"); 
   
}


void cackle(object obj) {
   obj->command("cackle");
}
