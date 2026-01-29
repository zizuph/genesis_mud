// passage1.c
// grace aug 1994

inherit "/d/Krynn/solamn/hctower/spur/room/std_pass.c";
#include "../local.h"
#define WPASS \
   ({  \
      ROOM + "passage2", \
      ROOM + "passage3", \
      ROOM + "passage4", \
      ROOM + "passage5", \
      ROOM + "passage6", \
      ROOM + "passage7", \
      ROOM + "passage8", \
      ROOM + "passage9", \
   })

object guard1, guard2;

reset_spur_room()
{
  if (!guard1)
    (guard1 = clone_object(KNIGHT))->move_living(0,this_object());
  if (!guard2)
    (guard2 = clone_object(KNIGHT))->move_living(0,this_object());
}

void
create_spur_room()
{
   AE(ROOM + "passage2", "west", 0);
   clone_object(SOBJ + "l2d2a")->move(TO);

   make_the_room("@@wpass_desc@@");

   reset_spur_room();

}

string wpass_desc()
{
  string *roomfiles;
  object *inv, *live, *dead, room;
  int i;

  roomfiles = WPASS;
  inv = ({});
  for (i = 0; i < sizeof(roomfiles); i++)
    {
    if ((room = find_object(roomfiles[i])) != 0)
      inv += all_inventory(room);
    }

  if (inv && sizeof(inv) > 0)
    {
    live = FILTER_LIVE(inv);
    dead = FILTER_DEAD(inv);

  if (sizeof(live) > 0)
      return ("Further west in the passage you can see " +
              COMPOSITE_LIVE(live) + ".\n");

    }
    return ("The passage to the west seems to be clear.\n");
}
