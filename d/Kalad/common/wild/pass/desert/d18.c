inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("The Caravan Route, within the waste\n"+
      "There are two obvious exits: northwest, southeast");
   set_long("The Great Kalad Waste, a desert of immense proportions "+
      "stretches out before you in all directions. The bleakness of the "+
      "waste is only further enhanced by the swirling sand that constantly "+
      "blows against you, while the unrelenting Kaladian sun beats down "+
      "from above, its harsh rays searing exposed flesh. "+
      "Several large boulders lie just off the route to the southwest. "+
      "The Caravan Route heads to the northwest and southeast.\n"+
      "There are two obvious exits: northwest, southeast.\n");
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
   add_item(({"large boulders","boulders","large boulder","boulder"}),
      "Huge rocks easily as large as a good-sized merchant wagon. They lie "+
      "to the southwest, running almost parallel to the Caravan Route. It "+
      "does seem possible, however, to walk between them, as they are not "+
      "that closely spaced.\n");
   add_exit(CPASS(desert/d17),"northwest",0,3);
   add_exit(CPASS(desert/d19),"southeast",0,3);
   add_exit(CPASS(desert/grass/g1),"southwest","@@msg");
   set_noshow_obvious(1);
}
msg()
{
   write("Stepping past the boulders you emerge onto verdant grassland!\n");
   return 0;
}
