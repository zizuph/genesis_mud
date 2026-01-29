/*
 * This is the Palanthas placer.
 *
 * It will place a number of npcs in the town.
 */
#pragma no_clone

inherit "/d/Krynn/std/placer";

#include "local.h"

void
create_placer()
{
    set_area_name("Palanthas");

    set_base_path(TDIR);
    set_unit_path(LIV);
    set_area_path(ROOM);
    
    add_group("streets", 
        ({ "street1", "street10", "street11", "street12", "street13", 
               "street15", "street16", "street17", "street18", "street19", 
               "street2", "street20", "street21", "street22", "street3", 
               "street4", "street5", "street6", "street7", "street8", 
               "street9" }));
    
    add_area_unit("streets", "city_guard", 8);
    
}
