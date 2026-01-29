
/* 
   coder(s):    Amelia

   history:    5/8/95    coded by Amelia
               19/8/96   minor alterations by Maniac 

   purpose:    beach bum's house, for mermaid quest
   exits:    out (to /d/Calia/mountain/sea_path3.c)

   npcs:       HERMIT
*/

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

object hermit; 

void
reset_room()
{
    if (!objectp(hermit))  { 
        hermit = clone_object(SEA_CREATURES + "hermit");
        hermit->move_living("into the hut", TO);
    } 
}

void
create_room()
{
   set_short("A thatched hut");
   set_long("This is a hut made from thatched sea grasses. "+
      "The western side of it, which faces the sea, is "+
      "completely open to the elements. The floor is simply "+
      "sand. Shells of various kinds are strewn around it. "+
      "An opening in the thatch leads out. "+
      "There is not much here except a mat in one corner, "+
      "and it seems whoever lives here, must be very poor.\n");

   add_item((({"sea grasses", "grasses", "thatched sea grasses"})),
      "The grasses are sea grasses and dried pampas fronds. "+
      "They are woven together to make the walls and ceiling.\n");
   add_item((({"walls", "ceiling", "western side"})),
      "The walls and ceiling, woven from grasses, are not "+
      "very sturdy. The entire western side is open to "+
      "a view of the sea.\n");
   add_item((({"view", "western view", "west", "sea"})),
      "You look out at the Calian sea to the west, which "+
      "extends all the way to the horizon. "+
      "Below at the foot of the sand dune, a white sandy beach "+
      "extends north and south. There is a line of large "+
      "boulders that extends from the beach on the northern "+
      "side out into the sea.\n");

   add_prop(ROOM_I_IS, 1);
   add_prop(ROOM_I_LIGHT, 1);
   add_prop(ROOM_I_INSIDE, 1);

   add_exit(BEACH+"sea_path3", "out", 0,0);

   reset_room();
}

