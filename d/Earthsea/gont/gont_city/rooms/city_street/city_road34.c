#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Cobbled street in Gont Port");
    set_long("The cobbled street ends here in front"+
        " of a large official looking stone building"+
        " bearing the white emblem of the Lord of Gont"+
        " above the door. A short stairway of grey granite"+
        " leads up to the door, standing open to allow"+
        " visitors to enter. In front of the stairway are"+
        " two stone bowls, one on each side, filled with"+
        " white flowers. To the east you can see"+
        " the tall city wall behind the low wooden buildings"+
        " lining the side of the road. Small gardens"+
        " in front of them make this area bright and pleasant"+
        " with green grass lawns and tall trees planted in"+
        " them.\n");
    add_item("building","Just to the north is a large"+
        " stone building looking somewhat malpositioned"+
        " among the low wooden houses. Above the door"+
        " is the white emblem of the Lord of Gont, making"+
        " you think this is an official building.\n");
    add_item("wall","The high crenelated city wall is"+
        " visible behind the low buildings to the east. The"+
        " street seems to follow it north and south.\n");
    add_item("street","The street is cobbled and quite"+
        " narrow, leading in the south direction alongside"+
        " the high city wall visible behind the low"+
        " wooden buildings to the east.\n");
    add_item(({"low buildings","wooden buildings"}),
        "The low wooden buildings seem to be residentials"+
        " for one family, having small gardens in front"+
        " with green grass lawns and fruit trees.\n");
    add_item("bowls","Stone bowls filled with large"+
        " white flowers stand in front of the stairway"+
        " leading up to the large house.\n");
    add_item("flowers","The flowers are snow-white"+
        " with a pleasant scent.\n");
    add_item("stairway","A stairway of grey granite"+
        " rock leads up to the wide open doors.\n");
    add_item("emblem","Above the door you can see the"+
        " white emblem of the Lord of Gont, making you think"+
        " this building is an official one rather than a"+
        " private home.\n");
    add_item("gardens","In front of each low wooden"+
        " building is a small garden, with green grass lawns"+
        " and fruit trees. Among other, you can see apple"+
        " and plum trees.\n");
    add_item("lawns","Green grass lawns cover the ground"+
        " of the small gardens. Most seem to be well-tended"+
        " and cut short but some are more wild grown.\n");
    add_item((({"trees", "fruit trees"})),
        "In some of the gardens you can"+
        " see fruit trees growing among the grass and"+
        " bushes. You can see apple and plum trees, among"+
        " other kinds.\n");
    add_cmd_item((({"apple", "fruit", "plum"})), "pick",
        "The fruit is not ripe enough yet.\n");
    add_exit("city_road29", "south");
}
