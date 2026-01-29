inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
   set_short("Side road in Leah");
   set_long("   The road is crowded with people. Most of them are women "+
      "doing their everyday shopping. Elven women visit the shops to buy and "+
      "sell their goods. Perhaps in one of these shops you could "+
      "find a gift for a friend. From the inn to your south "+
      "you can smell freshly baking bread and hearty soup cooking. "+
      "To the north and east of you are two "+
      "more shops where the Elven people of Leah and visitors alike do business.\n\n");
   
   add_exit(VILLAGE_DIR + "tapshop" ,"north", "@@no_way@@");
   add_exit(VILLAGE_DIR + "road", "west");
   add_exit(VILLAGE_DIR + "shop", "east");
   add_exit(VILLAGE_DIR + "inn", "south");
}

int
no_way()
{
    write("The tapestry shop is open only to residents of Leah. " +
        "Perhaps it will open soon for visitors.\n");
    return 1;
}
