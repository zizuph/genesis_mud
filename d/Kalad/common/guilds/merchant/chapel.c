inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/caravan/guild/default.h"
create_room()
{ 
   ::create_room();
   INSIDE;
   set_short("A small chapel devoted to Ammercia");
   set_long("A small chapel devoted to Ammercia, Patron Goddess of "+
      "merchants and trading.\n");
   add_prop(ROOM_M_NO_ATTACK, "The feeling of peace is too great here.\n");
   add_exit(CVAN(guild/joinroom),"east",0,-1,-1);
}
init()
{
   ::init();
   
   add_action("start","start");
}
int start(string s)
{
   if(s =="here" && (IS_MEMBER(TP)))
      {
      TP->set_default_start_location("/d/Kalad/common/caravan/guild/chapel");
      write("You will start here from now on.\n");
      return 1;
   }
   
   write("Either you can't type or you are not a member. Please try again.\n");
   return 1;
}
