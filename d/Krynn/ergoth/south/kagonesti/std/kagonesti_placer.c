#pragma no_clone

inherit "/d/Krynn/std/placer";

#include "local.h"

void
create_placer()
{
    set_area_name("Kagonesti Forest");
    set_base_path(STD);
    set_unit_path(LIVING);
    set_area_path(ROOMS);
    add_group("forest", ({
    "forest/forest00", "forest/forest01", "forest/forest02", "forest/forest03",
    "forest/forest04", "forest/forest05", "forest/forest06", "forest/forest07",
    "forest/forest08", "forest/forest09", "forest/forest10", "forest/forest11",
    "forest/forest12", "forest/forest13", "forest/forest14", "forest/forest15",
    "forest/forest16", "forest/forest17", "forest/forest18", "forest/forest19",
    "forest/forest20", "forest/forest21", "forest/forest22", "forest/forest23",
    "forest/forest24", "forest/forest25", "forest/forest26", "forest/forest27",
    "forest/forest28", "forest/forest29", "forest/forest30", "forest/forest31",
    "forest/forest32", "forest/forest33", "forest/forest34", "forest/forest35",
    "forest/forest36", "forest/forest37", "forest/forest38", "forest/forest39",
    "forest/forest40", "forest/forest41"}));
    add_group("huts", ({
    "huts/hut01", "huts/hut02", "huts/hut03", "huts/hut04", "huts/hut05",
    "huts/hut06", "huts/hut07", "huts/hut08", "huts/hut09", "huts/hut10"}));
    add_area_unit("forest", "kagonesti", 20);
    add_area_unit("forest", "hare", 1);
    add_area_unit("huts", "nightbird", 1);
    add_area_unit("huts", "kagonesti_child", 10);
}
