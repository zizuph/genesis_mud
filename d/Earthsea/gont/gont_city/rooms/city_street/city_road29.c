#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

private object woman;

public void
reset_room()
{
    if(!objectp(woman))
    {
        woman = clone_object("/d/Earthsea/gont/gont_city/liv/woman");
        woman->move(this_object());
        woman->command("emote strolls in.");
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Cobbled street in Gont Port");
    set_long("The cobbled street continues, following"+
        " the high city wall visible behind the low wooden"+
        " buildings lining the road on the east side."+
        " To the northwest another road leads in between"+
        " the houses. In"+
        " front of the houses are small gardens with green"+
        " grass lawns and a fruit tree here and there. On"+
        " the other side of the street are higher two-story"+
        " buildings packed close together to give room for"+
        " as many citizens as possible. This seems to be"+
        " living quarters for average citizens of Gont"+
        " Port. To the south the street becomes more narrow"+
        " and darker, as it enters the poorer areas of"+
        " the city.\n");
    add_item("wall","The high crenelated city wall is"+
        " visible behind the low buildings to the east. The"+
        " street seems to follow it north and south.\n");
    add_item("street","The street is cobbled and quite"+
        " narrow, leading in north-south direction alongside"+
        " the high city wall visible behind the low"+
        " wooden buildings to the east.\n");
    add_item(({"low buildings","wooden buildings"}),
        "The low wooden buildings seem to be residentials"+
        " for one family, having small gardens in front"+
        " with green grass lawns and fruit trees.\n");
    add_item(({"two-story buildings","higher buildings"}),
        "On the west side of the street are higher two-story"+
        " wooden buildings with many apartments to give"+
        " room for as many as possible.\n");
    add_item("gardens","In front of each low wooden"+
        " building is a small garden, with green grass lawns"+
        " and fruit trees. Among other, you can see apple"+
        " and plum trees.\n");
    add_item("lawns","Green grass lawns cover the ground"+
        " of the small gardens. Most seem to be well-tended"+
        " and cut short but some are more wild grown.\n");
    add_item("trees","In some of the gardens you can"+
        " see fruit trees growing among the grass and"+
        " bushes. You can see apple and plum trees, among"+
        " other kinds.\n");
    add_cmd_item((({"apple", "fruit", "plum"})), "pick",
        "You do not find any fruits ripe enough to pick here.\n");
    add_exit("city_road34", "north");
    add_exit("city_road30", "northwest");
    add_exit("city_road27", "south");
    reset_room();
}
