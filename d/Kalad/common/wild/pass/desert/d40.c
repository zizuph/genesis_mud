/* Modified by Tapakah, 11/2008, to link to Cirath */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("The Caravan Route, edge of the waste");
   set_long("The Great Kalad Waste, a desert of immense proportions "+
      "surrounds you from all directions. The ever-present swirling sand, "+
      "coupled with the harsh Kaladian sun only further enhances the utter "+
      "bleakness of this landscape. The unrelenting heat seems to sap the "+
      "strength from your very being.\n"+
      "The lands to the southeast, however, seem a bit different than "+
      "your present location.\n"+
      "The Caravan Route heads to the northwest and southeast.\n");
   add_item(({"caravan route","route"}),"A cobblestoned roadway that "+
      "shows the effects of heavy travel and the torturous environment.\n");
   add_item(({"great kalad waste","great waste","kalad waste","waste","landscape"}),
      "An apparently endless wasteland, the heat causes your vision to "+
      "blur, making the horizon shift and waver.\n");
   add_item(({"horizon"}),"A thin line in the distance.\n");
   add_item(({"swirling sand","sand"}),"It swirls and billows all about "+
      "you, limiting your vision severely.\n");
   add_item(({"kaladian sun","sun"}),"Its unrelenting rays have helped "+
      "turn this land into a harsh wasteland where little survives.\n");
   add_item(({"lands","land"}),"The land to the southeast seems more "+
            "reddish than the waste, with a kind of a brick-like hue.\n");
   add_exit(CPASS(desert/d39),"northwest", 0, 3);
   add_exit(CPASS(desert/d41),"southeast", 0, 3);
}
msg()
{
   write("The smell of flowers fades away into the wind.\n");
   return 0;
}
block()
{
   write("As you begin to travel to the southeast, a band of heavily armed, "+
      "and armoured warriors mounted on horses quickly dissuades you "+
      "from entering their land. You are forced back.\n");
   return 1;
}
