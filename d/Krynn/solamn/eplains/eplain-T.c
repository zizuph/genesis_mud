#include "local.h"
inherit TDIR+"eplain_base";

/*object goblin;

void
reset_road_room()
{
    if (goblin)
      return;
    goblin = clone_object(GOBLIN);
    goblin->move_living("xxx",TO);
}
*/

public void
create_eplains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("On a road before the dark forests of Throtyl");
    set_long("You are on a road leading east and west. West, the " +
      "Plains of Solamnia stretch out before you. To the east, " +
      "you can see a forest.\n");
    add_item(({"road","ancient road"}),
      "This is an ancient road, a bit overgrown with grass, but " +
      "usable.\n");
    add_item(({"plains","plains of solamnia","bushes"}),
      "The plains stretch out to the west from here, all you can " +
      "see is the light green of the bushes and the grass.\n");
    add_item(({"trees", "forest", "forests", "woods", "throtyl",
      "stormshire forest"}),
      "A bit to the east, a dense forest can be seen. It looks gloomy, " +
      "and a sense of danger lies in the air. The road disappears " +
      "into the forest.\n");
/*
    add_item(({"border watch","watch","borderwatch","guard","border guard"}),
      "These are two goblins stationed here to prevent anyone from " +
      "continuing east on the road and from entering the forest.\n");
*/

    add_std_exits();
    add_exit(THROTL_LINK,"east","@@closed@@",3,0);
}

int
closed()
{
    write("You follow the road into the gloomy forest...\n");
    return 0;
}

