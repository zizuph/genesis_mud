/* Ashlar, 21 Aug 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <filter_funs.h>

inherit SEWER_BASE;

#define BELOW_HUT   NSEWER + "below_hut"

string
long_descr()
{
    return "You are in a cramped spillway chute. To the south the " +
    "chute slants slightly downwards, but to the north it is much " +
    "more steep, making further travel north impossible. Above you, " +
    "light shines down from a grating. A stream of water flows " +
    "slowly along the bottom of the chute.\n";
}

void
create_neraka_room()
{
    set_short("in a spillway chute");
    set_long("@@long_descr");

    add_item(({"chute","spillway chute"}),"@@long_desc");
    add_item(({"water","stream of water"}),"The stream of water flows " +
      "slowly to the south. It is gathered in a small pool here.\n");
    add_item(({"pool","small pool"}),"The water is gathered in a small " +
      "pool just below the grating.\n");
    add_item("grating","The grating is quite a way up, and you see " +
      "nothing except light shining down from it.\n");
    add_item("light","Light shines down from the grating above.\n");
    add_item(({"bottom","bottom of chute"}),"A small stream of water " +
      "flows slowly along the bottom of the chute, which is very slippery " +
      "thanks to that.\n");
    add_cmd_item("grating","open","You can not even reach the grating, " +
      "much less open it.\n");

    add_exit(NSEWER + "s7", "south");
}


