// pass3l1.c
// grace sept 1994


inherit "/d/Krynn/solamn/hctower/spur/room/std_pass2.c";
#include "../local.h"

#define NPASS \
({  \
      ROOM + "pass2l1", \
      ROOM + "pass1l1", \
 })

#define SPASS \
 ({ \
     ROOM + "pass4l1", \
     ROOM + "void", \
 })

object guard1, guard2;

reset_spur_room()
{
   if (!guard1)
      (guard1 = clone_object(KNIGHT))->move_living(0,this_object());
   if (!guard2)
      (guard2 = clone_object(KNIGHT))->move_living(0,this_object());
   guard2->set_leader(guard1);
   guard1->team_join(guard2);
}


void
create_spur_room()
{
   AE(ROOM + "pass2l1", "north", 0);
   AE(ROOM + "pass4l1", "south", 0);   

   ACI("air", "smell",
      "It is cool and damp. Surprisingly, there is no musty smell.\n");
   clone_object(SOBJ + "l1d2b")->move(TO);

   make_the_room("The air is chilly and smells of fresh water.  "+
   "@@npass_desc@@@@spass_desc@@");

   reset_spur_room();
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

