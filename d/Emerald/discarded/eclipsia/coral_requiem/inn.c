inherit "/std/room";
inherit "/lib/pub";

#include <macros.h>
#include "../edefs.h"

void create_room()
{
   string sign = 
   "  Fresh water        5 cc\n"+
   "  Seaweed soup      80 cc\n"+
   "  Haddock plate    140 cc\n"+
   "  Salmon platter   250 cc\n"+
   "  Lobster tails    400 cc\n\n"+
   "Use 'buy water with silver' if you want to be "+
   "specific as to what kind of coins you wish to use, "+
   "or 'test buy soup' to see what would happen if you typed "+
   "'buy soup'. 'buy 5 water' would get you 5 waters, but it takes "+
   "some time to tap them all up.\n";
   
   set_short("Hot Springs Inn");
   set_long("   Welcome to the Hot Springs Inn. Bustling with " +
      "customers, the inn usually does excellent business. " +
      "Merfolk sit about the tables eating and conversing. You " +
      "notice a menu hanging on the wall by the bar.\n\n");
   
   add_item("merfolk", "Happy merfolk sit about the tables laughing " +
      "and conversing, and eating of course.\n");
   add_item("menu", sign);
   add_item(({ "table", "tables" }), "The tables are made of blue, " +
      "shimmering coral, and are polished to a shine.\n");
   add_cmd_item("menu", "read", sign);
   
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_drink( ({ "water", "waters", "fresh water", "fresh waters" }), 
      "water", "fresh", 10, 0, 5, 0, 0,
      "It looks really clear and fresh.\n");
   add_food(({"seaweed","seaweed soup","soup","soups"}),
      "soup","seaweed",65,80,"cup of seaweed soup",
      "cups of seaweed soup",
      "The dark green soup smells very good, and is very " +
      "nutritious.\n");
   add_food(({"haddock","haddocks", "haddock plate"}),
      "haddock", 0, 100, 140, "haddock plate",
      "haddock plates",
      "It looks like quite a mouthful. The white " +
      "meat looks delicious, just beware of the bones...\n"); 
   add_food( ({ "salmon", "salmons", "platter", "salmon platter" }),
      "platter", "salmon", 200, 250, 0, 0,
      "It looks quite delicious. Your mouth start to water.\n", 0);
   add_food( ({ "lobster", "lobsters", "tail", "tails", "lobster tails",
            "lobster tails" }),
      "tail", "lobster", 375, 400, "plate with lobster tails",
      "plates with lobster tails",
      "This is really gourmet food. It just looks delicious.\n", 0);
   
   add_exit(CRDIR + "cr15", "west");
}

void
init()
{
   ::init();
   init_pub();
}
