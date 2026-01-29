inherit "/std/room";
inherit "/lib/pub";

#include "defs.h"

void
create_room()
{
   object drunk;
   int    i;
   
   set_short("Bar at the Inn");
   set_long(break_string("This room has been fashioned into a pub. "+
         "Many drunken sailors come here to drink and have "+
         "a good time. This room is slanted from the overall "+
         "slant of the wreckage. All these drunks have quite a "+
         "time trying to compensate for the slant, most of "+
         "them stay seated.\n",76)+"There is a menu here.\n");
   
   add_item("menu", "There seems to be writing on it.\n");
   add_cmd_item("menu", "read", "@@menu_desc@@");
   
   add_prop(ROOM_I_INSIDE, 1);
   for (i=0 ; i<2 ; i++) {
      drunk=clone_object(NPC_DIR + "humanoids/drunk");
      drunk->move(this_object());
   }
   
   add_drink(({"fantasy", "quartermaster"}), "fantasy","quartermaster",
      200, 20, 60, 0, 0, "It is a quartermaster's favorite drink.\n",0);
   add_drink(({"dog", "salty dog"}), "dog", "salty",
      100, 5, 12, 0, 0, "It is as salty as the sea.\n", 0);
   add_drink("mutiny","mutiny", 0,
      75, 50, 240, 0, 0, "This drink looks very strong.\n", 0);
   add_drink(({"mast", "captain's mast", "captains mast"}), "mast",
      ({"captain's","captains"}),
      150, 40, 180, 0, 0, "Sailors shake in their boots at the name of this drink.\n",
      0);
}

string
menu_desc()
{
   return "The menu reads:\n\n"+
   "  Salty Dog              - 12  cc\n"+
   "  Quartermaster Fantasy  - 60  cc\n"+
   "  Captain's Mast         - 180 cc\n"+
   "  Mutiny                 - 240 cc\n";
}

void
init()
{
   ::init();
   init_pub();
}
