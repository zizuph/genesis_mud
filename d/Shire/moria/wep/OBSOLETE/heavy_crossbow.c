#include "defs.h"
#include "/d/Shire/moria/include/bows.h"

inherit "/d/Shire/moria/wep/crossbow";

create_crossbow()
{
    set_name("crossbow");
    set_short("heavy crossbow");
    add_adj("heavy"); 
    bolt_type = HEAVY_BOLT;
    set_long("This is a heavy crossbow.\n");
}
