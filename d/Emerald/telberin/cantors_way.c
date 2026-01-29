#include "defs.h"

inherit TELBERIN_STREET;

public void
create_cantors_way()
{
}

nomask void
create_telberin_street()
{
    config_street_room("Arts", "Cantors Way");

    set_em_long("\n");

    create_cantors_way();
}
