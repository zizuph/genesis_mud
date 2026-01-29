/*
 * bolt.c 
 */

#include "defs.h"
#include "/d/Shire/moria/include/bows.h"

inherit "/d/Shire/moria/wep/missile";

create_missile()
{
    set_name("bolt");
    add_adj("heavy");
    set_short("heavy bolt");
    set_long("This is a heavy bolt for use in heavy crossbows.\n");
    set_missile_type(HEAVY_CROSSBOW_BOLT);
    set_missile_hit(100);
    set_missile_pen(100);
}

