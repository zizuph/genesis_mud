inherit "/std/room";

#include "default.h"

void create_room()
{
    set_short("Domain entrance");
    set_long(break_string("This is the wizard's entrance into the "+
             "Emerald domain. To the west you can see the " +
             "great Tower of Domains, while the magnificent workroom "+
             "of Emerald lies to the south.\n", 70));
    add_exit("/d/Genesis/wiz/dom_a2", "west", 0);
    add_exit(DOMAIN_DIR + "workroom", "south", 0);
}
