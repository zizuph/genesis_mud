inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* modified by Antharanos */
   void
create_room()
{
   set_short("Near the Trade Square");
   set_long("Ahead lies the trade square. This is the major attraction of "
      +"the trade district, where merchandise of average quality can "
      +"be bought at a small price.\n");
   add_item(({"doors","door"}),"These are the doors to homes. They are all "
      +"locked.\n");
   add_item(({"homes", "home"}),"These are the homes of the lowerclassed "
      +"merchants of Kabal. The houses are "
      +"rather plain.\n");
   add_item(({"signs"}),"These are signs with the names of shops plastered "
      +"on them. They are all in blazing colours to attract "
      +"the few people who come shopping here.\n");
   add_exit(TRADE(wall/wall5),"east");
   add_exit(TRADE(tsquare/t2),"west");
   hear_bell = 2;
}
