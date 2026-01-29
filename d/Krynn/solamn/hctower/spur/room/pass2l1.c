// pass2l1.c
// grace sept 1994


inherit "/d/Krynn/solamn/hctower/spur/room/std_pass2.c";
#include "../local.h"

#define NPASS \
({  \
      ROOM + "pass1l1", \
      ROOM + "void", \
 })

#define SPASS \
 ({ \
     ROOM + "pass4l1", \
     ROOM + "pass3l1", \
     ROOM + "void", \
 })



void
create_spur_room()
{
   AE(ROOM + "pass1l1", "north", 0);
   AE(ROOM + "arch5", "east", 0);
   AE(ROOM + "pass3l1", "south", 0);   

   ACI("air", "smell",
      "It is cool and damp. Surprisingly, there is no musty smell.\n");

   make_the_room("The air is chilly and smells of fresh water.  "+
   "@@npass_desc@@@@spass_desc@@");

}

string npass_desc()
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
         return ("Further north in the passage you can see " +
         COMPOSITE_LIVE(live) + ".");
   }
   return ("The passage to the north appears to be clear.");
}

string spass_desc()
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
         return ("  The southern end of the hall is occupied by " +
         COMPOSITE_LIVE(live) + ".\n");
   }
   return ("\n");
}
