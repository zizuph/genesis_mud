// std passage
// grace aug 1994

#include "/sys/stdproperties.h"
#include      "../local.h"

inherit SPURRM;

#define HALL \
   ({  \
      ROOM + "greathall", \
      ROOM + "void", \
   })

/*
 * This function defines the room.
 */
varargs void
make_the_room(string extra_long)
{
    if (!extra_long) { extra_long = "\n"; }

    set_name("passage");
    SHORT("Second floor hallway");
    LONG("Torches placed in sconces at regular intervals down the "+
        "passage make it bright as day.  The stone floor is swept "+
        "and polished to a high sheen that reflects the light.  " +
         extra_long);

    AI(({"torches","torch"}), "The torches burn brightly.\n");
    AI("sconces", "Stone brackets made for holding torches.\n");
    AI(({"floor","stone floor"}),
        "It is so shiny you can see your reflection in it.\n");
    AI(({"reflection", "my reflection"}), "Yes, sure enough, that "+
        "is a distorted image of your face. At least, you hope it "+
        "is distorted. You've seen draconians prettier than that!\n");
    AI(({"walls", "wall", "passage", "passageway"}),
        "The walls are made of smooth dark stone. The passageway is "+
        "wide enough for five men to walk abreast.\n");
    AI(({"arch","arches"}),
        "The arches are very narrow and run from the high ceiling " +
        "down to a small, waist-high wall that runs the length of " +
        "the passage. The arches provide a view of what appears to " +
        "be a very large room.@@hall_desc@@");
    ACI(({"arch","arches"}), "enter", "You cannot fit. The archway " +
        "is too narrow.\n");

    INSIDE;
    LIGHT;
}

string hall_desc()
{
  string *roomfiles;
  object *inv, *live, room;
  int i;

  roomfiles = HALL;
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
      return (" In that room you can see " +
              COMPOSITE_LIVE(live) + ".\n");
    }
    return (" The room seems to be empty.\n");
}
