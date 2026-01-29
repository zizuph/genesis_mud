#include "defs.h"

CONSTRUCT_ROOM
{
   set_short("The study");
   set_long(
      "You have arrived in a once cosy place, which seems to have been a "+
      "study. Now however the room is smelling badly, probably due to an "+
      "orc which lies dead here in a corner. There is a dark passage "+
      "leading out of the room to the west.\n");
   add_item("orc",
      "The orc's remains are a poor sight. It is stenching foul, and the "+
      "cadaver's bones are clearly visible. Why it was killed here you "+
      "can not imagine, and all that he once may have possessed is not "+
      "here anymore.");
   add_item(({"room","ceiling","floor","wall","walls"}),
      "The room is built in wood, therefore giving its nice aura, but "+
      "as it has not been visited in ages, the decay has rotted most of "+
      "it. Nothing of value seems to be here.");
   WEST("cavern");
   reset();
}
/* rope might be causing problems with orc movement */
/* so it will be removed until problem is solved */
/*
object rope;

RESET_ROOM
{
   if (!rope || !present(rope, TO))
      {
      rope = clone_object(MORIA_OBJ+"rope");
      rope -> move(TO);
   }
}
*/
