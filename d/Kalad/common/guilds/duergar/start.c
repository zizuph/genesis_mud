inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/duergar/default.h"
create_room()
{ 
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("A resting area for the clan-members");
   set_long("A resting area for the clan-members. "+
      "Here you can start each time you are again ready "+
      "for some slaughtering and looting. All you do is to "+
      "write <start here>, and you will begin at your own "+
      "clans hideout. To enter the world of blood and gold, "+
      "go south.\n");
   add_prop(ROOM_M_NO_ATTACK, "The strange feeling of peace is too great here.\n");
   add_exit("/d/Kalad/common/guilds/duergar/train","south",0,-1,-1);
   set_noshow_obvious(1);
}

void
init()
{
   ::init();
   
   add_action("start","start");
}

int 
start(string s)
{
   if(s =="here" && (IS_MEMBER(TP)))
      {
      TP->set_default_start_location("/d/Kalad/common/guilds/duergar/start");
      write("From now on you shall begin your adventures and intrigues "+
         "from this chamber, in the hideout of the Duergar-clan.\n");
      return 1;
   }
   
   write("Either you can't type or you are not a member. Please try again.\n");
   return 1;
}
