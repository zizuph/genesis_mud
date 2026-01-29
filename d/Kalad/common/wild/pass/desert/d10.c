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
      "strength from your very being. "+
      "Great rolling sand dunes are visible to the southwest, among which "+
      "a narrow path lies. "+
      "The Caravan Route takes a turn here, heading to the northwest and "+
      "in the east.\n");
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
   add_item(({"great rolling sand dunes","great dunes","rolling dunes","sand dunes","dunes","dune"}),
      "Towering dozens of feet in height in some places, the dunes are "+
      "as hills in other climes, albeit constantly shifting ones.\n");
   add_item(({"narrow path","path"}),"A slight depression among the "+
      "rolling dunes.\n");
   add_exit(CPASS(desert/d9),"northwest",0,3);
   add_exit(CPASS(desert/d11),"east",0,3);
   add_exit(CPASS(desert/sand/d1),"southwest","@@msg",3);
}
msg()
{
   write("A sudden gust of wind lashes sand across your face, like the "+
      "feel of a whip...\n");
   return 0;
}
