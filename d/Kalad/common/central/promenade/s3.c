inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;

/* by Korat */
create_room()
{
   ::create_room();
   hear_bell = 3;
   set_short("Promenade");
   set_long("You walk along the Promenade, a street laid with cobblestones. "+
      "Many buildings line the sides of the street, but what captivates your "+
      "eyes is a huge tower to the northwest; the Citadel. All manner of refuse "+
      "litters the ground here, but the road northwestwards looks in a better "+
      "shape.\n");
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
   add_item(({"citadel","tower"}),"When you study the Citadels tower from "+
      "this distance, you are struck by the sight of the hugh dome and its "+
      "tower in the center. A huge bell is inside it that from time to time "+
      "clangs loudly.\n");
   add_item(({"refuse"}),
      "Discarded pieces of trash lie across the street surface, bits and "+
      "pieces of scrap metal, useless fragments of wood and even a beggar "+
      "or two. Its less of it here though compared to the other streets "+
      "you have walked in this city.\n");
   add_exit(CENTRAL(promenade/s2), "northeast",0);
   add_exit(CENTRAL(promenade/s4), "southwest",0);
   add_exit(CENTRAL(citadel/s1), "northwest",0);
   set_alarm(1.0,0.0,"reset_room");
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
