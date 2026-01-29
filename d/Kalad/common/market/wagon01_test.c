inherit "/d/Kalad/std_room.c";

#include "/d/Kalad/defs.h"
#include <ss_types.h>

int strawSearch,floorSearch,lootFound;

create_room()
{
   strawSearch = 0;
   floorSearch = 0;
   lootFound   = 0;
   
   ::create_room();
   
   set_short("\n" + "On top of a rickity wagon");
   set_long("\n" +
      "    You are in the flatbed of a rickity, old "+
      "wagon. There seems to be rust and rot all over "+
      "the place. The bed of the wagon is filled with "+
      "straw. "+
      "\n");
   
   add_item("straw","The straw is old, damp, and rotten.\n");
   add_item( ({"floor","board","boards","floorboards",
            "bed","flatbed","flat bed","bottom"}), "@@exaFloor@@");
   
   add_cmd_item("straw","move","@@move_straw@@");
   
   add_prop(OBJ_S_SEARCH_FUN, "search_room");
   
   add_exit(MRKT_PATH(m15), "southwest");
   add_exit(MRKT_PATH(m19), "northeast");
}

reset_room ()
{
   /*  ::reset_room(); */
   strawSearch = 0;
   floorSearch = 0;
}

string
exaFloor()
{
   string ret;
   
   if (strawSearch == 0)
      ret="The floor of the wagon is covered with straw.\n";
   else
      ret="The floorboards are in good shape.  Most are still intact.\n";
   return ret;
}

string
move_straw()
{
   string ret;
   
   if(strawSearch == 0)
      {
      ret="You move the straw aside and reveal the " +
      "floorboards of the wagon.\n";
      strawSearch = 1;
      SAYNAME("Clever "," moves the straw aside revealing " +
         "the floorboards of the wagon.\n");
   }
   else
      ret="The straw has already been moved aside.\n";
   
   return ret;
}

string
search_room(object player, string str)
{
   if(str == "straw")
      {
      strawSearch = 1;
      
      SAYNAME("", " searches the straw and reveals the "+
         "floorboards of the wagon.\n");
      return (BS("You rumage through the straw and reveal the "+
            "floorboards of the wagon.\n"));
   }
   else if ((str == "floor") || (str == "board") ||
         (str == "boards") || (str == "floorboards")) {
      if (strawSearch == 0) {
         return (BS("You can't see the floor through " +
               "all that straw. Maybe you should move it.\n"));
            }
      else if (player->query_skill(SS_AWARENESS) > 10) {
         floorSearch = 1;
         return (BS("You found a compartment in the floorboards.\n"));
         ret}
      else
         return (BS("You think there's a hollow area in the "+
            "floorboards, but you can't seem to find the opening.\n"));
   }
   else
      return 0;
}
