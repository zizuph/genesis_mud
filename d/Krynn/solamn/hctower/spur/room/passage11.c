// passage11.c
// grace aug 1994

inherit "/d/Krynn/solamn/hctower/spur/room/std_pass.c";
#include "../local.h"

#define EPASS \
   ({  \
      ROOM + "passage1", \
      ROOM + "passage2", \
      ROOM + "passage3", \
      ROOM + "passage4", \
      ROOM + "passage5", \
      ROOM + "passage6", \
      ROOM + "passage7", \
      ROOM + "passage8", \
      ROOM + "passage9", \
   })
          

void
create_spur_room()
{
   AE(ROOM + "passage9", "east", 0);
   AE(ROOM + "passage10", "north", 0);
   AE(ROOM + "passage12", "south", 0);

   make_the_room("In this room the north-south hall intersects " +
      "with a passage running east-west.@@epass_desc@@");

}

epass_desc()
{
  string *roomfiles;
  object *inv, *live, room;
  int i;

  roomfiles = EPASS;
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
      return ("  You can see " + COMPOSITE_LIVE(live) + 
              " in the eastern passage.\n");
    }
    return ("  The east passage is empty.\n");
}
