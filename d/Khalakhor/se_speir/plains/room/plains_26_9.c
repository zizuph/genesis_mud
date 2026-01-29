#include "plains.h"

inherit PLAINBASE;

public void
reset_room()
{
   set_searched(0);
}


public void
create_khalakhor_room()
{
    proxim = (["river"  : ({0, "west"})]);
    create_plain();
    set_short("In a farm yard on a grassy plain");
    set_long("   You are in the yard of a rural dwelling set on the rolling "+
             "plains near the river which is just to the west. The low "+
             "grasses of the plain have been trodden down here, only "+
             "a few clumps struggling to grow in the hard-packed sod. "+
             "The home to the east is typical of those in this "+
             "area, a small stone dwelling with a thatched roof. A "+
             "narrow dirt path leads along the river's edge to the "+
             "northeast.\n");

    add_item(({"house","home","dwelling"}),
       "It is a one-level, and probably one-room, rural home made "+
       "of large irregular stones masoned together, with a thatched "+
       "roof and a chimney. It seems to be open to the east.\n");
   add_item(({"yard","grass","sod","ground","dirt"}),
       "Trampled by feet of the inhabitants, and probably some animals, "+
       "the grass barely grows here in the yard, struggling with common "+
       "yard weeds. The ground is mostly the hard-packed "+
       "dirt of the local sod.\n");


    add_exit(PLAINS + "plains_27_8",  "northeast");
    add_exit(PLAINS + "home_27_9",    "east");
    add_exit(PLAINS + "plains_27_10", "southeast");
    add_exit(PLAINS + "plains_26_10", "south");
    add_exit(PLAINS + "plains_25_10", "southwest");
}

public int *
query_global_coords()
{
    return ({3,0});
}

public void
setup_plains_herbs() // yard; restrict to dandelion
{
    herbs = (({"/d/Krynn/common/herbs/dandelion"}));
    set_up_herbs(herbs, ({"grass","here","weeds"}), 3);
}
