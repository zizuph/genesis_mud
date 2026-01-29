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
      "The Caravan Route heads to the northwest and southeast.\n");
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
   add_exit(CPASS(desert/d22),"northwest",0,3);
   add_exit(CPASS(desert/d24),"southeast",0,3);
   set_alarm(2.0,0.0,"msg");
}
msg()
{
   tell_room(TO,"Strange as it may be, for a split second you could "+
      "have sworn that you saw a flying carpet overhead. It was probably "+
      "just a mirage brought about by the desert heat...\n");
   return 1;
}
