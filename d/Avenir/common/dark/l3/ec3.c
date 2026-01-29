// file name: ~Avenir/common/dark/l3/ec3.c
// creator(s):
// revision history:
// purpose:
// note:
// bug(s):
// to-do: Probably entrance to level 4 of Untedark.

inherit "/d/Avenir/inherit/room";
#include "/d/Avenir/common/dark/dark.h"

object trapdoor;

create_domain_room()
{
    set_short("Musty cave");
    set_long(
"The tunneling seems to have stopped here. There are dark streaks in the\n"+
"walls which appear to be exhausted veins of adamantite.\n");

    add_exit(L3+"e2","south",0);
    add_exit(L4+"n16","down",0);

    BLACK
    IN
}

