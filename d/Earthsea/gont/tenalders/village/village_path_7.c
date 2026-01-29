/*
 * coded by Amelia 6/1/97
 * path through Ten Alders
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

public void
create_earthsea_room()
{
    set_short("village path");
    set_long("A gravel path. The path winds among several " +
        "thatch-covered huts that comprise this small village, " +
        "situated on a somewhat more level area of the mountain " +
        "side.\n");
    add_item((({"path", "gravel path"})),
        "The gravel path winds among some small thatch-covered " +
        "huts that comprise this small village.\n");
    add_item((({"village", "huts", "thatch-covered huts"})),
        "The village is small and apparently rather poor, " +
        "comprised of only a few small thatch-covered huts. Here and " +
        "there you see a villager going about his business, and " +
        "pine and herbal smelling smoke fill the air.\n");
    add_exit("village_path_6", "northwest");
}
