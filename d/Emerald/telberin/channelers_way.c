#include "defs.h"

inherit TELBERIN_STREET;

public void
create_channelers_way()
{
}

nomask void
create_telberin_street()
{
    config_street_room("Magic", "Channelers Way");

    set_em_long("\n");

    create_channelers_way();
}
