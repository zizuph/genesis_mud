// passage1.c
// grace aug 1994

inherit "/d/Krynn/solamn/hctower/spur/room/std_pass2.c";
#include "../local.h"

#define NPASS \
   ({  \
      ROOM + "passage11", \
      ROOM + "passage10", \
   })
#define SPASS \
   ({  \
      ROOM + "passage13", \
      ROOM + "landing3", \
   })         

object guard1, guard2, guard3, guard4;

reset_room()
{
  if (!guard1)
    (guard1 = clone_object(KNIGHT))->move_living(0,this_object());
  if (!guard2)
    (guard2 = clone_object(KNIGHT))->move_living(0,this_object());
    guard2->set_leader(guard1);
    guard1->team_join(guard2);
  if (!guard3)
    (guard3 = clone_object(KNIGHT))->move_living(0,this_object());
    guard3->set_leader(guard1);
    guard1->team_join(guard3);
  if (!guard4)
    (guard4 = clone_object(KNIGHT))->move_living(0,this_object());
    guard4->set_leader(guard1);
    guard1->team_join(guard4);
}


void
create_room()
{
   SHORT("Center of passage");

   AE(ROOM + "passage11", "north", 0);
   AE(ROOM + "greathall", "east", 0);
   AE(ROOM + "passage13", "south", 0);
   AE(ROOM + "vestibule", "west", 0);  

   make_the_room("Here you can go east into the Great Hall or west " +
      "toward the Chapel of Paladine.@@npass_desc@@@@spass_desc@@");

   reset_room(); 
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
      return ("  To the north you can see " + COMPOSITE_LIVE(live) +
              ".");
    }
    return ("  The hall is clear to the north.");
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
      return ("  " + COMPOSITE_LIVE(live) + " can be seen in the southern " +
          "end of the hall.\n");
    }
    return ("  Nothing is moving to the south.\n");
}
