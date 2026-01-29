

inherit "/lib/area_handler";

#include <stdproperties.h>

create_area()
{
    set_map("/d/Cirath/katakoro/wastes/area_handler/ah_map");
    add_desc("m", ({ ({ ROOM_NORMAL, 0, 1 }),
                     ({ "a field",
  "The hills roll endlessly and majestically on.",
  "The field looks endless, everything looks the same.",
  "Bitter cold can be felt everywhere, eminating from the hills." }),
                     ({ "path", "A wide, twist trade rout." }),
                     ({ }) }));
    add_desc("p", ({ ({ ROOM_NORMAL, 0, 1 }),
                     ({ "a path",
   "You are travelling upon a hardened, cold, dirt trail winding "+
   "its way through the wastes."}),
                     ({ "insect", "You can't find any around here." }),
                     ({ }) }));
  add_bound("A", "/d/Cirath/katakoro/wastes/area_handler/ah_entry");
  add_bound("E", "/d/Cirath/katakoro/wastes/area_handler/ah_entry2");

}


