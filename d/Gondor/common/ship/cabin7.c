#pragma save_binary

inherit "/d/Genesis/ship/cabin";
#include "/d/Gondor/common/lib/time.h"

#include "/d/Gondor/defs.h"

void
create_cabin()
{
    set_short("A small cabin inside the large river boat");
    set_long(BSN("Even though the river boat is very large, this cabin "
      + "is very small. But of course, on a boat travelling on a river "
      + "there is less need to go under deck than on sea-going vessels. "
      + "On a small table there are some maps and the whole room is "
      + "illuminated by a lantern in the ceiling. A set of plain "
      + "wooden stairs leads up to the deck, while another set of "
      + "even plainer stairs leads down."));
    add_item("lantern", BSN("The lantern is secured in the ceiling. "
      + "It is a large brass lantern with a large oil container that "
      + "should last quite a while."));
    add_item(({"table", "small table"}), BSN(
        "Long ago, the surface of the table must have been polished. "
      + "Now there is little left of that. Scratches and cuts from "
      + "nautical intruments and eating knives have left their traces "
      + "among ink stains and circular spots that were made by glasses "
      + "and bottles."));
    add_item(({"map", "maps"}), BSN("The maps are nautical maps and "
      + "there seem to be several doublets, some being riddled with marks "
      + "lines and notations while others seem brand new. You wonder "
      + "why the captain of a river boat should use these sea charts."));
    add_exit(SHIP_DIR + "deck7",      "up", 0);
    add_exit(SHIP_DIR + "slavedeck7", "down", 0);
}
