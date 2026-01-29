inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* by Korat */
create_room()
{
   ::create_room();
   hear_bell = 3;
   set_short("Gladiator Row");
   set_long("You walk along the Gladiator Row, a street laid with cobblestones. "+
      "Many buildings line the sides of the street, but what attracts your "+
      "attention is a huge circular construction to the east. It is the "+
      "Gladiatoral arena of Kabal. You can walk to the southeast "+
      "or towards a crossroad in the northwest. All manner of refuse "+
      "litters the ground here.\n");
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
   add_exit(CENTRAL(high-gladiator),"northwest");
   add_exit(CENTRAL(gladiator/s2),"southeast",0);
}

