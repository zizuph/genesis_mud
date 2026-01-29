// passage6.c
// grace aug 1994

inherit "/d/Krynn/solamn/hctower/spur/room/std_pass.c";
#include "../local.h"
#define WPASS \
   ({  \
      ROOM + "passage7", \
      ROOM + "passage8", \
      ROOM + "passage9", \
   })

#define EPASS \
   ({  \
      ROOM + "passage1", \
      ROOM + "passage2", \
      ROOM + "passage3", \
      ROOM + "passage4", \
      ROOM + "passage5", \
   })

void
create_spur_room()
{
   AE(ROOM + "passage5", "east", 0);
   AE(ROOM + "passage7", "west", 0);

   make_the_room("A series of arches line the " +
       "south wall.  @@wpass_desc@@@@epass_desc@@");

}

string wpass_desc()
{
  string *roomfiles;
  object *inv, *live, room;
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
  if (sizeof(live) > 0)
      return ("Further west in the passage you can see " +
              COMPOSITE_LIVE(live) + ".  ");
    }
    return ("The passage to the west seems to be clear.  ");
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
      return ("In the eastern passage you can see " +
              COMPOSITE_LIVE(live) + ".\n");
    }
    return ("The east passage is empty.\n");
}
