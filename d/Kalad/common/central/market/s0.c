inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* by Korat */
create_room()
{
   ::create_room();
   hear_bell = 3;
   set_short("Market street");
   set_long("The Market Street stretches onwards to the northwest and "+
      "southeast, and even though you see buildings line the sides of the "+
      "intersection you decide that this place is really uninteresting. "+
      "Further southeastwards though, you notice some kind of apparatus "+
      "that captivates your attention. "+
      "All manner of refuse litters the ground here.\n");
   add_item(({"road","roadways","street"}),
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
   add_item("apparatus","It looks like some kind of a lift that can bring "+
      "things and persons downwards to the port area.\n");
   add_exit(CENTRAL(lift_room), "southeast",0);
   add_exit(CENTRAL(market/s1),"northwest");
}

