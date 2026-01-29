/* 
Citadel, dining room.
Made by Korat 
Feb 14. 1995 
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_M_NO_TELEPORT, 1);
   hear_bell = 2;
   set_short("Citadel, dining room");
   set_long("You see a single, long table here in this dining room, "+
      "with a few chairs surrounding "+
      "it. In the northern end of the table a larger chair is situated, "+
      "without doubt being the High Lords chair. The walls are decorated by "+
      "some nice paintings that match the brownish paneling on the walls. "+
      "Either the decorator or the High Lord himself has a good taste when it "+
      "comes to comfort.\n");
   
   add_item(({"painting","paintings"}),"They portraits different scenarios "+
      "of people, nature and a battle-scene here and there.\n");
   add_item("table","The table is of polished redwood, giving it a burgundy "+
      "colour that matches the panelings on the walls.\n");
   add_item(({"panel","paneling"}),"The paneling must be of oak, and has "+
      "been lighly torched to give the wood a darker brownish touch in its "+
      "colour. Together with the table it manages to dampen the lights from "+
      "the candles, giving a relaxed atmosphere in the room.\n");
   add_item("chair","The High Lords chair has several intricate decorations "+
      "engraved into the wood, giving it a timeless feel of elegance.\n");
   
   add_exit(CENTRAL(citadel/cit22),"south",0,-1,-1);
   add_exit(CENTRAL(citadel/cit20),"northwest",0,-1,-1);
}
