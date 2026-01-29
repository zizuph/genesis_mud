inherit "/std/room";
#include "defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
     bring_room_mob("dwarf", TZ_MINTHOR+"npc/dcook.c", 1, 1);
}

create_room()
 {
  set_short("Kitchen");
  set_long("You have entered a large kitchen. Smells assault your "
	+"nostrils, and the sight of all the food makes you hungry. "
	+"A huge oven is baking what appears to be massive loaves "	
	+"of bread, while a pot is boiling over on the top of a flame. "
	+"Chaos reigns here, but out of the chaos comes what is "
	+"reputed to be the best cuisine in Tyr.\n");
  add_item("kitchen","You are in the largest one you have ever seen.\n");
  add_item("food","It looks really good. Too bad you can't tell "
	+"what it is.\n");
  add_item("oven","It is a massive oven made of stone. It could "
	+"probably cook enough food for a small army.\n");
  add_item("pot","It looks to be made of either steel or iron, which "
	+"in itself is rare, it is also the largest pot you have ever "
	+"seen, probably big enough to fit at least an entire kank.\n"); 
  add_item("flame","The flame is burning red hot, and easily boiling "
	+"water that is in the pot.\n");
  add_item(({"house","mansion"}),"You are inside of it.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  INSIDE
  add_exit(TZ_MINTHOR + "mh18","northeast", 0);
  add_exit(TZ_MINTHOR + "mh16","east", 0);
  add_exit(TZ_MINTHOR + "mh13","west");
   reset_room();
}

