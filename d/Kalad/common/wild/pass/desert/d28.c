inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("The Caravan Route, within the waste");
   set_long("The Great Kalad Waste, a desert of immense proportions "+
      "surrounds you from all directions. The ever-present swirling sand, "+
      "coupled with the harsh Kaladian sun only further enhances the utter "+
      "bleakness of this landscape. The unrelenting heat seems to sap the "+
      "strength from your very being.\n"+
      "Far to the northeast lie the Desertrise mountains.\n"+
      "A verdant oasis lies to the southwest...or is it just a mirage?\n"+
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
   add_item(({"desertrise mountains","mountains","mountain"}),"A low "+
      "series of mountains that lies within the center of the Great Kalad "+
      "Waste, towering above the surrounding area.\n");
   add_item(({"verdant oasis","oasis"}),"A place that seems to lie "+
      "just off of the Caravan Route, filled with trees, grass and most "+
      "importantly, water!\n");
   add_item(({"trees","tree"}),"A stand of them is clustered around "+
      "what appears to be a large pool of water.\n");
   add_item(({"grass"}),"It covers the ground around the pool.\n");
   add_item(({"pool of water","pool","water"}),"A bubbling spring here "+
      "in the otherwise waterless waste.\n");
   add_item(({"mirage"}),"The oasis seems to wave and flutter before "+
      "your eyes, as if it were about to disappear.\n");
   add_exit(CPASS(desert/d27),"northwest",0,3);
   add_exit(CPASS(desert/d29),"southeast",0,3);
   add_exit(CPASS(desert/oasis/o1),"southwest","@@msg");
}
msg()
{
   write("You walk into the oasis, the coolness of the shade a pleasant "+
      "change from the oppressive heat of the desert.\n");
   return 0;
}
