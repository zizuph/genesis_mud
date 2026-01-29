/*
ROOM: Fire Brigade bedroom of the firemen
BY:   Korat
DATE: Aug 28, 1994
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
int burning;
int done_burned;

void
create_room()
{
  ::create_room();
   burning = 0;
   done_burned = 0;
   set_long(@@mylong@@);
  hear_bell = 2;
  
  add_prop(ROOM_I_INSIDE, 1);
  
  set_short("This is the common bedroom of the firemen");
  
  add_prop(ROOM_NO_TIME_DESC, 1);
    
  add_exit(CENTRAL(plaza/fb_rm21), "west", 0, 0, 0);

  add_item(({"beds", "bunkbeds"}),  
    "You come to the conclusion that any kind of bed should be made "+
    "illegal in a fire brigade. But then, maybe it already is.\n"
  );
   add_item("candle","It is burning slowly with a bright yellow flame.\n");
}

init()
{
   ::init();
   add_action("light","light");
   add_actoin("light","ignite");
}
mylong()
{
   if(burning)
      return "The rooms is filled with hot, burning flames that licks around "+
      "your body. You have severe problems with breathing in the thick "+
      "black smoke. A man seems to be stuck in the corner of the room, "+
      "with flames all around him!\n";
   if (!burning && done_burned)
      return "The rooms is ruined. It seems like a fire has roamed "+
      "around and destroyed this place; The walls are blackened "+
      "and all the furniture is ruined until uselessness.\n";
   if (!burning && !done_burned)
   return "You are on the second floor of the fire brigade, "+
      " in the bedroom of "+
    "all the firemen. There are some bunkbeds standing against the wall "+
    "and it seems that they are filled by firemen, judging from the snores. "+
    "No wonder these guys always arive when the fire has already burned "+
      "itself out!\n";
}

