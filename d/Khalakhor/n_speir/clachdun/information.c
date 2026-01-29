#include "/d/Khalakhor/sys/paths.h"
#include "local.h"

inherit INFO_BASE;

public void
create_info()
{

    aliases = ([
      "shop": ({"shop", "store"}),
      "post": ({"post", "post office"}),
      "pub": ({"pub","tavern","inn","bar"}),
      "bank": ({"bank","gnome deposit"}),
      "bladesmith": ({"bladesmithy","bladesmith forge"}),
      "blacksmith": ({"blacksmithy","blacksmith forge"}),
      "stables": ({"stable", "stables", "horse stables"}),
      "town_square": ({"town square", "city square", "village square"}),
      "keep": ({"keep gates", "keep entrance"}),
      "throne": ({"throne room", "throne of Clach Dun"}),
      "tower": ({"bell tower", "tower", "lookout tower"}),
    ]);

    coords = ([
      "shop": ({6,12}),
      "post": ({5,13}),
      "pub": ({5,9}),
      "bank": ({7,16}),
      "bladesmith": ({12,3}),
      "stables": ({14,11}),
      "town_square": ({8,10}),
      "keep": ({8,8}),
      "throne": ({8,1}),
      "tower": ({8,13}),
      "blacksmith": ({12,4}),
    ]);

    area_name = "Clach Dun";
    global_coords = CLACHDUN_CORDS;
}
