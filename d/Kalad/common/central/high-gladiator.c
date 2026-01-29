/* 
 * /d/Kalad/common/central/high-gladiator.c
 * Purpose    : Road connection between high and gladiatorstreet
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
   set_short("High Street");
   set_long("You walk along the High Street, a street laid with cobblestones. "+
      "Many buildings line the sides of the street, and above them you "+
      "notice a huge tower to the southwest; the Citadel. If you walk southwards "+
      "it looks like you will end up in a center, while northwards this road "+
      "leads to the Caravan area. Another road leads southeastwards: the "+
      "Gladiator Row. All manner of refuse "+
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
   add_item(({"citadel","tower"}),"When you study the Citadels tower from "+
      "this distance, you can't see much except a hugh bell inside it. That "+
      "must be where all that clanging comes from.\n");
   add_item(({"refuse"}),
      "Discarded pieces of trash lie across the street surface, bits and "+
      "pieces of scrap metal, useless fragments of wood and even a beggar "+
      "or two.\n");
   add_exit("/d/Kalad/common/caravan/high-harvest","north",0);
   add_exit(CENTRAL(high/s1),"south");
   add_exit(CENTRAL(gladiator/s1),"southeast",0);
}

