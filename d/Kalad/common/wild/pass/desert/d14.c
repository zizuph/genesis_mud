inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("The Caravan Route, within the waste");
   set_long("The vastness of the Great Kalad Waste stretches in every "+
      "direction, in all its glorious bleakness. Swirling sand blows "+
      "constantly against you, while the unrelenting Kaladian sun beats "+
      "down from above, searing exposed flesh with its harsh light.\n"+
      "The Caravan Route heads to the west and east, journeying straight "+
      "across the waste.\n");
   add_item(({"caravan route","route"}),"A cobblestoned roadway that "+
      "shows the effects of heavy travel and the torturous environment.\n");
   add_item(({"great kalad waste","great waste","kalad waste","waste"}),
      "An apparently endless wasteland, the heat causes your vision to "+
      "blur, making the horizon shift and waver.\n");
   add_item(({"horizon"}),"A thin line in the distance.\n");
   add_item(({"swirling sand","sand"}),"It swirls and billows all about "+
      "you, limiting your vision severely.\n");
   add_item(({"kaladian sun","sun"}),"Its unrelenting rays have helped "+
      "turn this land into a harsh wasteland where little survives.\n");
   add_exit(CPASS(desert/d13),"west",0,3);
   add_exit(CPASS(desert/d15),"east",0,3);
}
