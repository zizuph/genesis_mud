inherit "/d/Shire/room";
#include "/d/Shire/moria/defs.h"

void
create_room()
{
   set_short("A warm hot place, deep in the mines");
   set_long("The air is only slightly warmer here, "+
	    "but the steam rising from the ground gets much thicker. "+
	    "Low rumbling sounds echo from the somewhere nearby in the "+
	    "blackness. The air pulses with a bright red glow, "+
	    "nearly in rhythm with the mysterious sounds.\n");


   add_item(({"steam","ground","air"}),
   "The steam rises from the ground, heating the air in this place. "+
   "You wonder what could make so much heat. The steam is so thick "+
   "you disappear below the knee.\n");

   add_item(({"red glow","glow","eerie red glow","sound"}),
   "The glow brightens and fades in time with the low rumbling "+
   "sounds that echo from within the darkness.\n");


   add_prop(ROOM_I_INSIDE, 1);

   add_exit("/d/Shire/moria/mines/lair/lair","west",0,3);
   add_exit("/d/Shire/moria/mines/lair/lair4","north",0,3);

//   set_noshow_obvious(1);

}
