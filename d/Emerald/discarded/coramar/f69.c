#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{
    set_short("A misty forest path");

    set_long("   The forest seems strange here. The characteristic cold "+
             "wind is blocked by the tight clustering of the small "+
             "trees. The ground is almost dry enough to prevent your "+
             "feet from sinking here, and the mist even seems thinner. "+
             "You have a very strong hunch that this particular path "+
             "through the forest is not natural. The quiet is calming and peaceful. "+
             "In the distance to the east, you can see the dim shadow of a small, square "+
             "structure of some kind, though it looks to be covered "+
             "in moss.\n\n");

    add_fexit(CORAMAR+"f68", "northwest", 0);
    add_fexit(CORAMAR+"f70", "east", 0);
}
