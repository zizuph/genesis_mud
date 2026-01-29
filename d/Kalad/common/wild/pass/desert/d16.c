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
      "The Caravan Route journeys to the west and east.\n");
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
   add_exit(CPASS(desert/d15),"west","@@message",3);
   add_exit(CPASS(desert/d17),"east",0,3);
   set_alarm(2.0,0.0,"msg");
}
msg()
{
   tell_room(TO,"The air before you ripples due to the intense heat.\n");
   return 1;
}
void
message()
{
   int i;
   i = random(3);
   if(i < 1)
      {
      TP->catch_msg("A hot, dry wind blows against you from the east.\n");
      return;
   }
   else
      if(i < 2)
      {
      TP->catch_msg("A great rumbling sound, somewhat like thunder, resounds "+
         "in the distance.\n");
      return;
   }
   else
      TP->catch_msg("Wind-blown sand lashes you across the face.\n");
   return;
}
