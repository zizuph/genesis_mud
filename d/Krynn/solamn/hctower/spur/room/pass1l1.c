// pass1l1.c
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
   AE(ROOM + "pass2l1", "south", 0);   

   ACI("air", "smell",
      "It is cool and damp. Surprisingly, there is no musty smell.\n");

   clone_object(SOBJ + "l1d4a")->move(TO);

   make_the_room("This end of the hall is quiet and appears to be unused.  "+
   "@@spass_desc@@");

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
         return ("The southern end of the hall is occupied by " +
         COMPOSITE_LIVE(live) + ".\n");
   }
   return ("\n");
}
