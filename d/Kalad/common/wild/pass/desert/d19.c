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
      "To the northeast lies a large salt flat.\n"+
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
   add_item(({"large salt flat","large flat","salt flat","flat"}),"A "+
      "large area of the desert upon which a massive amount of salt lies "+
      "exposed to the air.\n");
   add_exit(CPASS(desert/d18),"northwest",0,3);
   add_exit(CPASS(desert/salt/s10),"northeast","@@blind",3);
   add_exit(CPASS(desert/d20),"southeast",0,3);
}
blind()
{
   write("You are nearly blinded by the intensity of the sun's reflection "+
      "off of the salt crystals before you.\n");
   return 0;
}
