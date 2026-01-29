/* 
 * /d/Kalad/common/central/market-promenade.c
 * Purpose    : Road connection between market and promenadestreet
 * Located    : /d/Kalad/common/central/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/* 
 * /d/Kalad/common/central/market-promenade.c
 * Purpose    : Road connection between market and promenadestreet
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
   set_short("Intersection Market street and the Promenade");
   set_long("This large intersection is where two busy roadways, Market "+
      "Street and the Promenade, cross paths. From here the Promenade stretches "+
      "northeast deeper into the Central district, while the Market street "+
      "leads towards the northwest and southeast. Many buildings line the sides "+
      "of the intersection, but above them you do notice a huge tower to the "+
      "north; the Citadel. All manner of refuse litters the ground here.\n");
   add_item(({"intersection","roadways"}),
      "Both streets are paved in slate-grey cobblestones that look worn "+
      "and cracked from heavy use, though still in good condition for such "+
      "a heavily-travelled crossroads.\n");
   add_item(({"buildings"}),
      "Most of the structures are wooden, and are tightly packed along the "+
      "roadside. They are a mixture of shops and homes, with the shops most "+
      "likely catering to the needs of wandering travellers. The buildings "+
      "appear a bit weathered, just like the roadways, but are still in "+
      "good shape.\n");
   add_item(({"citadel","tower"}),"When you study the Citadels tower from "+
      "this distance, you can't see much except a hugh bell inside it. That "+
      "must be where all that clanging comes from.\n");
   add_item(({"refuse"}),
      "Discarded pieces of trash lie across the street surface, bits and "+
      "pieces of scrap metal, useless fragments of wood and even a beggar "+
      "or two.\n");
   add_exit(CENTRAL(promenade/s4), "northeast",0);
   add_exit(CENTRAL(market-circle),"southeast",0);
   add_exit(CENTRAL(market-promenade),"northwest","@@block",0);
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
block()
{
   write("The way is blocked by a barricade.\n");
   return 1;
}

