inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("The Caravan Route, within the waste");
   set_long("The Great Kalad Waste, a desert of immense proportions "+
      "stretches out before you in all directions. The bleakness of the "+
      "waste is only further enhanced by the swirling sand that constantly "+
      "blows against you, while the unrelenting Kaladian sun beats down "+
      "from above, its harsh rays searing exposed flesh.\n"+
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
   add_exit(CPASS(desert/d29),"northwest",0,3);
   add_exit(CPASS(desert/d31),"southeast",0,3);
   set_alarm(2.0,0.0,"msg");
}
msg()
{
   tell_room(TO,"An eerie sound is carried to you by the wind, reminding you "+
      "of the mournful cries of the newly dead.\n");
   return 1;
}
