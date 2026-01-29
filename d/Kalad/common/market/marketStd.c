inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

void
create_room()
{
   ::create_room();
   
   set_short("\n" + "Inside the Market of Kalad");
   set_long(BS("\n"+
         "You are inside the marketplace of Kalad. "+
         "The ground beneath you is muddy from overuse and "+
         "dust covers everything.  The amount of people in the "+
         "area make it difficult to get your bearings. "+
         "\n\n"));
   
   add_item(({ "ground", "mud", "dirt", "dust" }), BS("\n"+
         "The mud on the ground is a couple of inches deep "+
         "and seems to cover everything.  Whatever "+
         "the mud can't reach, a layer of dust has. "+
         "\n\n"));
   
   hear_bell = 1; /*faint because of the noise from the crowd */
   
   add_prop(ROOM_I_HIDE,0); /* easy to hide: its _very_ crowded */
}

void
init()
{
   ::init();
   
   AA(list,listen);
}

int
list(string str)
{
   if((str != "")&&(str != "crowd")&&(str != "people")&&
         (str != "crowds")&&(str != "to crowd")&&
      (str != "to people")&&(str != "to crowds"))
   {
      write("Listen to what?\n");
      say(QCNAME(this_player()) + " listens to nothing.\n");
      
      return 1;
   }
   else
      {
      write(BS("\n"+
            "You hear the vendors hawking their wares and "+
            "many people engaged in barter.  Occasionally, you "+
            "hear the sounds of argument or fights as well as an "+
            "occasional, 'stop thief!'.\n\n"));
      say(QCNAME(this_player()) + " listens to the market sounds.\n");
      
      return 1;
   }
}

