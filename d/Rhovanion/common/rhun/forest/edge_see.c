#include "def.h"
inherit THIS_DIR+"room";

void add_stuff()
{
    add_item(({"plain","plains"}),"The plains of Rhun stretch"
        +" out before you, a vast and inhospitable piece of dry, parched"
        +" land.  You dare not wander out onto them.\n");
    add_item(({"tree", "trees", "forest"}), "The forest is"
        +" made up of tall, dense trees topped by dark, thick leaves."
        +"  It is oddly silent, as though all the woodland creatures had"
        +" been scared off.\n");
    add_item(({"sea","Sea","sea of rhun","Sea of Rhun"}),"The"
        +" vast expanse of the Sea of Rhun stretches out to the west, "
        +"its waves churning and crashing against each other and the shore."
        +"\n");
    add_herbs();
}
