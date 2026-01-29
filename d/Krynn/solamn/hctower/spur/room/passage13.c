// passage13.c
// grace aug 1994

inherit "/d/Krynn/solamn/hctower/spur/room/std_pass2.c";
#include "../local.h"

#define NPASS \
({  \
      ROOM + "passage11", \
      ROOM + "passage10", \
      ROOM + "passage12", \
 })
#define SPASS \
({  \
      ROOM + "void", \
      ROOM + "landing3", \
 })         

void
create_spur_room()
{
   SHORT("A short north-south passage");
   
   AE(ROOM + "passage12", "north", 0);
   AE(ROOM + "landing3", "south", 0);
   
   
   make_the_room("@@npass_desc@@@@spass_desc@@");
}

npass_desc()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;
   
   roomfiles = NPASS;
   inv = ({});
   for (i = 0; i < sizeof(roomfiles); i++)
   {
      if ((room = find_object(roomfiles[i])) != 0)
         inv += all_inventory(room);
   }
   
   if (inv && sizeof(inv) > 0)
      {
      live = FILTER_LIVE(inv);
      if (sizeof(live) > 0)
         return ("To the north you can see " + COMPOSITE_LIVE(live) +
         ".");
   }
   return ("The hall is clear to the north.");
}

spass_desc()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;
   
   roomfiles = SPASS;
   inv = ({});
   for (i = 0; i < sizeof(roomfiles); i++)
   {
      if ((room = find_object(roomfiles[i])) != 0)
         inv += all_inventory(room);
   }
   
   if (inv && sizeof(inv) > 0)
      {
      live = FILTER_LIVE(inv);
      if (sizeof(live) > 0)
         return ("  " + COMPOSITE_LIVE(live) + " can be seen in the " +
         "southern end of the hall.\n");
   }
   return ("  Nothing is moving to the south.\n");
}
