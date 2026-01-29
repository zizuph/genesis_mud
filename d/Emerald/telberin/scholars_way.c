#include "defs.h"

inherit TELBERIN_STREET;

public void
create_scholars_way()
{
}

nomask void
create_telberin_street()
{
    
    config_street_room("Scientific", "Scholars Way");

    set_em_long("\n");

    create_scholars_way();
}
