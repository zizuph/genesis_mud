#include "defs.h"

inherit TELBERIN_STREET;

public void
create_royal_circle()
{
}

nomask void
create_telberin_street()
{
    config_street_room(0, "the Royal Circle");
    set_em_long("Royal Circle is the center of the city where the Palace, "+
        "Keepers of Telberin, Temple, and other government buildings are. "+
        "The road that surrounds the Royal Circle bears the same name.\n");

    create_royal_circle();
}
