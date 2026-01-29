/* Created by Lucas */
/* Modified by Kieryn */
   

#include "/d/Emerald/eclipsia/edefs.h"
#include <stdproperties.h>
#include "/d/Emerald/defs.h"

inherit WATER_ROOM;

create_room()
{
   ::create_room();
   set_short("Caves around Coral Requiem");
   set_long("    Just to the south, a portal opens into a larger room. " +
      "North of here is the rest of the cave, and the way " +
      "to the central court. Merfolk can be seen coming in and out " +
      "of the doorway. You notice some of the mermaids drift by with " +
      "seashell purses around their shoulders. A sign hangs from the " +
      "doorway to the south.\n\n");
   
   add_item("sign", "The sign reads:  BANK\n");
   add_item(({"merfolk", "mermaid", "mermaids", "purses"}),
      "Merfolk go about their business as usual. Mermaids with " +
      "purses inlaid with shells go in and out of the doorway.\n");
   add_item(({"portal", "doorway", "opening"}),
      "Quite a crowded spot! Merfolk come and go from the opening. " +
      "A small sign hangs from the top of the doorway.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr23", "north");
   add_exit(CRDIR + "bank", "south");
}

