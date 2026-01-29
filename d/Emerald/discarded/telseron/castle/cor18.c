/*
 * Mirror corridor in castle of Telseron
 * By Finwe, November 1996
 */

inherit "/d/Emerald/telseron/castle/mirror_cor_base.c";
 
#include "/d/Emerald/defs.h"
#include "default.h"
 
void
create_mirror_corridor()
{
    add_exit( TCASTLE_DIR + "cor19", "east");
    add_exit( TCASTLE_DIR + "cor17", "west");
}
