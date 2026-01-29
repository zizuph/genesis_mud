inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"

void
create_room()
{
   set_short("A hot steamy place, deep in the mines");
   set_long("The air is much warmer in this place, "+
	    "though the floating steam seems to thin somewhat. "+
	    "Strange rumbling sounds echo from the darkness as "+
	    "the air throbs with an intense red aura, "+
	    "alternating primeval sounds with primary light.\n");


   add_item(({"steam","ground","air"}),
   "The steam rises from the ground, heating the air in this place. "+
   "The ground here is pocked with small depressions, covered with a "+
   "thin film of water.\n");

   add_item(({"red glow","glow","eerie red glow","sound"}),
   "The glow brightens and fades out of time with the low rumbling "+
   "sounds that echo from within the darkness.\n");

   add_item(({"water","film","depressions","depression","pock"}),
   "The water covering the pocked depressions is stale smelling and "+
   "has probably been here longer than you have been alive. The depressions "+
   "seem even older, and made by something very powerful.\n");

   add_prop(ROOM_I_INSIDE, 1);

   add_exit(MINES_DIR + "lair/lair","east",0,3);
   add_exit(MINES_DIR + "lair/lair5","north",0,3);

//   set_noshow_obvious(1);

}
