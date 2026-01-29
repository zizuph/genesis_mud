// passage10.c
// grace aug 1994

inherit "/d/Krynn/solamn/hctower/spur/room/std_pass2.c";
#include "../local.h"

#define SPASS \
   ({  \
      ROOM + "passage11", \
      ROOM + "passage13", \
      ROOM + "passage12", \
      ROOM + "landing3", \
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
   SHORT("End of passage");

  AE(ROOM + "stair9", "up", 0);  
   AE(ROOM + "passage11", "south", 0);

   reset_spur_room(); 

   make_the_room("Here the passage ends at the foot of a "+
      "winding stair.@@spass_desc@@");
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
      return (" " + C(COMPOSITE_LIVE(live)) + " can be seen in the southern " +
          "end of the hall.\n");
    }
    return ("  Nothing is moving to the south.\n");
}
