#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
create_forest()
{
    set_short("A misty forest path");


    set_long("   The forest seems to push in against the path from all "+
             "sides, as if trying to smother its contents. The huge trunks "+
             "of the trees begin to bend further over the path as it "+
             "continues gradually to the west and then north. Vines hang "+
             "down onto the path from limbs so far above they cannot "+
             "be seen. Peering around, you notice that you are completely "+
             "surrounded by a thick cloud of mist. Its moist grayness "+
             "dulls the outline of the path and turns ordinarily majestic "+
             "trees into nothing more than dark shadows beyond. Enormous "+
             "bushes and ferns thrust out of the forest floor everywhere, "+
             "making this path through the forest appear more like a "+
             "maze through a mist-shrouded jungle.\n\n");

    add_fexit(CORAMAR+"f14", "west", 0);
    add_fexit(CORAMAR+"f9", "southeast", 0);
}
