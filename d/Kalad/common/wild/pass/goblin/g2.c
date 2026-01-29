inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("The Caravan Route, Intersection");
   set_long("To the west lies the bulk of the towering Hespyre mountain "+
      "range, its dark shadow spreading across the land. Your immediate "+
      "surroundings consist of a low series of foothills, which continue to "+
      "the east. The outer fringes of the redwood forest surround you as "+
      "well, thinning the further east you go. The Caravan Route heads "+
      "off to the west and east, while a dirt pathway angles off to the "+
      "northeast.\n");
   add_item(({"caravan route","route"}),"A relatively wide band of cobblestoned "+
      "road that is showing the harsh effects of heavy usage and many years of "+
      "wind and rain.\n");
   add_item(({"intersection"}),"Where the Caravan Route is met by a "+
      "dirt pathway.\n");
   add_item(({"towering hespyre mountain range","towering range","hespyre range","mountain range","range","mountains","mountain"}),
      "A massive series of gigantic mountains that forms the eastern "+
      "boundary of the city-state of Kabal. Were it not for the Caravan "+
      "Route that travels through the mountainous area, the range would be an "+
      "insurmountable barrier to all travellers.\n");
   add_item(({"foothills"}),"Relatively small, rolling land that lies at "+
      "the foot of the much more massive Hespyre mountain range.\n");
   add_item(({"redwood forest","forest"}),"A mighty forest of gigantic "+
      "trees, whose encovering canopies help add to the shadowy aspect of the "+
      "land.\n");
   add_item(({"dirt pathway","pathway"}),"A rough, and apparently well-travelled "+
      "path that leads northeast, heading deeper into the surrounding "+
      "foothills.\n");
   add_exit(CPASS(goblin/g1),"west",0,2,1);
   add_exit(CPASS(goblin/g5),"northeast","@@msg",2,1);
   add_exit(CPASS(goblin/g3),"east",0,2,1);
}
msg()
{
   write("You feel a twinge of nervousness as you step onto the path.\n");
   return 0;
}
