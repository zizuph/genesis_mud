/* 
 * /d/Kalad/common/central/market-circle.c
 * Purpose    : Road connection between market and circlestreet
 * Located    : /d/Kalad/common/central/
 * Created By : Korat 1995
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* by Korat */
create_room()
{
   ::create_room();
   hear_bell = 3;
   set_short("Market street");
   set_long("Here a smaller road leads to the east through a small alley, "+
      "while Market Street stretches onwards to the northwest and southeast. "+
      "Many buildings line the sides of the intersection: the usual homes "+
      "and small shops that is spread out all over Kabal. All manner of "+
      "refuse litters the ground here.\n");
   add_item(({"road","roadways","alley"}),
      "Both streets are paved in slate-grey cobblestones that look worn "+
      "and cracked from heavy use, though still in good condition for such "+
      "heavily-travelled roads. The alley seems to lead towards the center "+
      "off this district.\n");
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
   add_exit(CENTRAL(circle/s12), "east",0);
   add_exit(CENTRAL(market/s3), "southeast",0);
   add_exit(CENTRAL(market-promenade),"northwest",0);
}

