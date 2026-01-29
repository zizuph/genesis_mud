inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
   object door;
   
   set_short("Outside tower");
   set_long("   You are standing on the main road in Leah north of the "+
            "town centre. To the north there are some gardens with a large "+
            "marble tower set in the middle of them. To the west there is the "+
            "bank of Leah that seems to be in daily use. The street is busy, "+
            "with people traveling in and out of the bank and through the town.\n\n");
   
   add_item(({"tower", "large tower", "large marble tower", "marble tower"}), "The tower "+ 
           "is tall and graceful, it's white marble arches towering into the sky.\n"); 
   add_item(({"road", "main road", "street"}), "This wide cobblestone road "+
           "goes east to west through town.  It is bustling with people.\n");
   add_item(({"people"}), "The people seem to be hurring around doing there "+
           "daily shopping.\n");
   add_item(({"cobblestone", "cobblestones"}), "The cobblestones are laid in "+
           "an intricate pattern.\n");
   add_item(({"garden","north", "gardens"}), "The brilliance and colour of the "+
           "garden spreads out everywhere. The true beauty of the garden is too "+
           "far away to truly appreciate.\n");
   add_item(({"west", "bank", "bank of Leah"}), "To the west you see the bank "+
           "of Leah.  A few of the villagers are doing there daily business there.\n");
   add_item(({"town", "center", "centre"}), "You can see the centre of town from "+
           "here.  There are many people bustling about the center.\n");

   add_exit(VILLAGE_DIR + "garden1","north");
   add_exit(VILLAGE_DIR + "road", "south");
   add_exit(VILLAGE_DIR + "bank", "west");
}

int
wiz_check()
{
   if(TP->query_wiz_level())
      return 0;
   write("Somehow, you feel that you should not go that way.\n");
   return 1;
}
