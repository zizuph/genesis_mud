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
      "Far to the northeast lies the Desertrise mountains, a mountain range "+
      "colored dark brown by the sand of the waste.\n"+
      "A trail leads to the northeast.\n"+
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
   add_item(({"desertrise mountains","mountains","mountain","mountain range","range"}),
      "A series of low mountains that rises within the center of the "+
      "Great Kalad Waste.\n");
   add_item(({"trail"}),"A rocky path that looks like it leads northeast "+
      "to the Desertrise mountains.\n");
   add_exit(CPASS(desert/d23),"northwest",0,3);
   add_exit(CPASS(desert/mount/m1),"northeast","@@msg",4);
   add_exit(CPASS(desert/d25),"southeast",0,3);
}
msg()
{
   write("Leaving the dusty Caravan Route behind, you set foot upon "+
      "the rocky path.\n");
   return 0;
}
