inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"

void
create_room()
{
   set_short("A hot steamy place, deep in the mines");
   set_long("The air is cool and dank for a change, "+
	    "though the steam does not go away entirely. "+
	    "Loud rumbling sounds assault your hearing, "+
	    "and the steam flickers red now and again.\n");



   add_item(({"steam","ground","air"}),
   "The steam rises from the ground, heating the air in this place. "+
   "The ground here is pocked with small depressions, covered with a "+
   "thin film of water.\n");

   add_item(({"red glow","glow","sounds","sound"}),
   "The glow brightens and fades out of time with the low rumbling "+
   "sounds that echo from within the darkness.\n");

   add_item(({"water","film","depressions","depression","pock"}),
   "The water covering the pocked depressions is covered by a thick "+
   "red film that is only partly translucent. "+
   "The depressions are a bit bigger here, and too big to be footprints.\n");

   add_prop(ROOM_I_INSIDE, 1);

   add_exit("/d/Shire/moria/mines/lair/lair","southwest",0,3);
   add_exit("/d/Shire/moria/mines/lair/lair2","south",0,3);
   add_exit("/d/Shire/moria/mines/lair/lair6","northwest",0,3);
}
