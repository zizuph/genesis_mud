#include "defs.h"

inherit STDROOM;

public string
which_way_east()
{
    if (file_name(TP->query_prop(LIVE_O_LAST_ROOM)) == query_exit()[0])
        return "Behind you to the east";
    else
        return "Off to the east";
}

public void
create_room()
{
    set_short("doors of the south cathedral");
    set_long("You are standing in a small alcove on the western " +
        "edge of the southern cathedral of " + CASTLE_NAME + ". " +
        "The alcove is shallow, but very tall and wide, taken " +
        "up almost entirely by a massive pair of solid wooden " +
        "doors, once richly polished and carved, now dried, " +
        "cracked, and worm-ridden, they hang sadly ajar from " +
    "siezed hinges. @@which_way_east@@, you can see a very large " +
        "room which once served as a chapel of some sort, evident " +
        "by the altar upon the dais at the far end, and the " +
        "numerous rows of wooden benches which line the floor. " +
        "A faint, multi-coloured light filters through some openings " +
        "in the cathedral, but they are out of your line of " +
        "sight, if they do exist.\n\n");

    add_item(({"ceiling", "roof"}),
        "The ceiling above you is invisible, enshrouded in shadows.\n");
    add_item(({"walls"}),
        "The walls flanking the alcove are simple in construction, " +
        "made from large blocks of grey stone.\n");
    add_item(({"doors", "door"}),
        "The doors practically form the east wall, or would, if " +
        "they could be closed. They are now just a husk of their " +
        "once-grandness, the carvings depicted on them now " +
        "undeterminable shapes of splintered and cracked wood.\n");
    add_item(({"floor", "ground"}),
        "The floor is made from simple flagstones.\n");

    INSIDE;

    add_exit(RUIN + "s_cathedral", "east");
    add_exit(RUIN + "build1-cath", "west");
}
