/* 
 * /d/Kalad/common/central/caravan-gladiator.c
 * Purpose    : Road connection between caravan and gladiatorstreet
 * Located    : /d/Kalad/common/central/
 * Created By : Korat 1995
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;

/* by Korat */
create_room()
{
   ::create_room();
   hear_bell = 3;
   set_short("intersection Gladiator Row and caravan Street");
   set_long("You stand in the intersection between the "+
      "Gladiator Row, a street laid with cobblestones, and Caravan Street. "+
      "Many buildings line the sides of the street, but what attracts your "+
      "attention is a huge circular construction to the north. It is the "+
      "Gladiatoral arena of Kabal and by walking northwest you will soon "+
      "be close to it. You can walk towards the Caravan district "+
      "northeastwards or towards the basket-lift, southwest. "+
      "Southeastwards you will end up at the trading square, where "+
      "goods for the common man are sold.\n");
   add_item(({"road","street","cobblestone","cobblestones"}),"This road is "+
      "paved in slate-grey cobblestones that look worn "+
      "and cracked from heavy use, though still in good condition for such "+
      "a heavily-travelled crossroads.\n");
   add_item(({"buildings"}),
      "Most of the structures are wooden, and are tightly packed along the "+
      "roadside. They are a mixture of shops and homes, with the shops most "+
      "likely catering to the needs of wandering travellers. The buildings "+
      "appear a bit weathered, just like the roadways, but are still in "+
      "good shape.\n");
   add_item(({"refuse"}),
      "Discarded pieces of trash lie across the street surface, bits and "+
      "pieces of scrap metal, useless fragments of wood and even a beggar "+
      "or two.\n");
   add_item(({"arena","gladiatoral arena","construction"}),
      "You watch the arena and are struck by the size of it. Standing three "+
      "levels high with several red banners flapping in the wind, it is a sight "+
      "to remember.\n");
   add_exit(CENTRAL(gladiator/s3),"northwest");
   add_exit(CENTRAL(caravan/s4),"northeast");
   add_exit(CENTRAL(caravan-circle),"southwest");
   add_exit(TRADE(to_central),"southeast");
}
reset_room()
{
   if (!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/cmilitia");
      ob1 -> arm_me();
      ob1 -> move_living("xxx", TO);
   }
}
