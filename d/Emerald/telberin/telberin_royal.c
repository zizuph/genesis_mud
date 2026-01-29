#include "defs.h"

inherit TELBERIN_STREET;

public void
create_telberin_royal()
{
}

nomask void
create_telberin_street()
{
    
    config_street_room("mercantile", "the Royal Circle");
    set_em_long("Royal Circle is the center of the city where the Palace, "+
        "Keepers of Telberin, Temple, and other government buildings are. "+
        "The road that surrounds the Royal Circle bares the same name.\n");

    add_item(({"circle", "royal circle"}),
        "Royal Circle is the center of the city where the Palace, "+
        "Keepers of Telberin, Temple, and other government buildings are. "+
        "The road that surrounds the Royal Circle bares the same name.\n");




    
create_telberin_royal();
}
