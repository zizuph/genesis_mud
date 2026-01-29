#include "defs.h"

inherit TELBERIN_STREET;

public void
create_artisans_way()
{
}

nomask void
create_telberin_street()
{
    
    config_street_room("Mercantile", "Artisans Way");

    set_em_long("\n");

    create_artisans_way();
}
