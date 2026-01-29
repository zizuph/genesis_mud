/* by Antharanos */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

#define KIOSK CENTRAL(test/kiosk)

object ob1;

create_room()
{
   ::create_room();
   hear_bell = 2;
   set_short("Intersection of Caravan and Harvest");
   set_long("This is the intersection of Caravan Street and Harvest Way. "+
      "To the north lies the Caravan district, while south is the Tradesmen's "+
      "district. Crowded buildings line the entire intersection, while further "+
      "southwest along Caravan Street, a massive circular structure, the "+
      "gladiatorial arena of Kabal, is visible. Animal refuse litters the "+
      "intersection.\n");
   add_item(({"intersection","caravan street","harvest way"}),
      "Both roadways are paved in slate-grey cobblestones that look worn "+
      "and slightly cracked, though still in good condition for such heavily "+
      "travelled roads.\n");
   add_item(({"buildings"}),
      "Small wooden structures, they probably serve the many travellers that "+
      "use Caravan Street and Harvest Way.\n");
   add_item(({"massive circular structure","circular structure","structure","arena"}),
      "Little detail can be made out from here, save for the immense size "+
      "of the structure.\n");
   add_item(({"animal refuse","refuse"}),
      "Examining the filth further, you discern the droppings of several "+
      "types of animals, with horses and oxen being most prominent.\n");
   add_exit("/d/Kalad/common/caravan/harvest/s2", "west",0);
   add_exit("/d/Kalad/common/caravan/caravan/s4", "northeast",0);
   add_exit("/d/Kalad/common/caravan/road1-harvest", "east",0);
   add_exit(CENTRAL(caravan/s1),"southwest");

   reset_room();
}


reset_room()
{
   KIOSK->load_me();
   if (!present(find_object(KIOSK)))
      KIOSK->move(TO);
   
/*
   if (!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/caravan/npc/cmilitia");
      ob1 -> move_living("xxx", TO);
   }
*/
}


block()
{
   write("The way is blocked by a barricade.\n");
   return 1;
}
