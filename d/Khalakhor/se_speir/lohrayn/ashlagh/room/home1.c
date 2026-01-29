// Ancient home of the Solsheyderi
inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/guilds/sean-rhian/room/kneelrm";
#include "defs.h"
#include <macros.h>
object   manach=1; // no manach for now
 
void reset_room()
{
   if (manach) return;
   manach=clone_object(NPC+"shmanach");
   manach->equip_me();
   manach->move(TO);
   tell_room(TO,QCNAME(manach)+" arrives.\n");
}
 
void create_khalakhor_room()
{
   set_short("an ancient stone house");
   set_long(
      "You are in a very old house made of stone. The thatch ceiling and "+
      "hard dirt floor tell of a more ancient and less fine time for "+
      "the village as compared to the other homes in the town. A "+
      "small fire pit sits in an alcove of the home in the northwest "+
      "corner, which must serve as a fireplace. The stone walls seem "+
      "to sag a bit, though the ceiling and its wood rafters look newer. "+
      "The home seems to be bare, except for a carpet on the floor and "+
      "a table which looks almost like an altar covered with burning "+
      "candles in the center. You feel a very old presence here.\n");
 
   add_item(({"home","house","room"}),
      "This is an old house built of stone, with a dirt floor and a "+
      "thatched ceiling. It seems to be extremely old.\n");
   add_item(({"wall","walls"}),
      "The walls are made of stone, unlike the wood plank houses which "+
      "populate the rest of the village. They seem to sag a bit, as if "+
      "they are tired of holding up their own weight over centuries.\n");
   add_item(({"roof","thatch","ceiling","rafters"}),
      "The ceiling of the home looks a bit newer, especially the thatch "+
      "which has been spread over the old wooden rafters.\n");
   add_item(({"alcove","pit","fire pit","fireplace","hearth"}),
      "There is a firepit in the northwest corner of the home, a "+
      "circular alcove in the wall with a small hole in the "+
      "ceiling for smoke to rise out. It doesn't seem to have been "+
      "used in a while.\n");
   add_item(({"carpet","floor"}),
      "The floor of the home is just hard-packed dirt, but packed so "+
      "hard and smooth it is almost stone. A carpet covers the center "+
      "of the floor, detailed with intricate scrollwork and circles in "+
      "a traditional celtic design.\n");
   add_item(({"table","altar"}),
      "The table sitting in the middle of the home on the carpet looks "+
      "old. It is made of wood and has no particular design. Nine pillar "+
      "candles sit on top if it, their flames burning quietly and still.\n");
   add_item(({"candles","candle","flames","flame"}),
      "There are nine thick pillar candles, each of a different color, "+
      "placed on top of the table. Their silent flames do not seem to "+
      "move, and they seem to give off a perfumed scent.\n");
   add_exit("court5","south");
   reset_room();
}
