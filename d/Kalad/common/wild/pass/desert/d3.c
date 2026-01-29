inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
void reset_room();
void create_brigands();
int sand_disturbed;
/* by Antharanos */
void
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
   add_item("sand","@@exa_sand");
   add_item(({"kaladian sun","sun"}),"Its unrelenting rays have helped "+
      "turn this land into a harsh wasteland where little survives.\n");
   add_exit(CPASS(desert/d2),"northwest",0,3);
   add_exit(CPASS(desert/d4),"southeast","@@msg",3);
    add_exit("/d/Cirath/ships/kalad/kalad_port.c","east",0,-1);
   reset_room();
}
msg()
{
   write("Sweat begins to form on your brow as the heat of the "+
      "Kaladian sun pounds into you.\n");
   return 0;
}
void
reset_room()
{
   sand_disturbed = 0;
   return;
}
string
exa_sand()
{
   if(sand_disturbed)
      return("You look intently at the billowing white sand around you..."+
      "but find nothing of concern.\n");
   set_alarm(6.0,0.0,"create_brigands");
   return("You look intently at the billowing white sand around you...\n");
}
void
create_brigands()
{
   int i;
   sand_disturbed = 1;
   for(i = 0; i < 6; i++)
   {
      clone_object("/d/Kalad/common/wild/pass/npc/d_brigand")
      ->move(TO);
      tell_room(TO,"A brigand jumps out of his hiding place in the sand!\n");
   }
}
