#pragma no_clone

inherit "/d/Krynn/std/placer";

#include "local.h"

void
create_placer()
{
    set_area_name("Throtyl");
    set_base_path(TDIR);
    set_unit_path(LIVING);
    set_area_path(ROOMS);

    add_group("forest", ({
        "throtyl-5-0-f","throtyl-6-0-f","throtyl-7-0-f",
        "throtyl-8-0-f","throtyl-9-0-f","throtyl-4-1-f",
        "throtyl-5-1-f","throtyl-6-1-f","throtyl-7-1-f",
        "throtyl-8-1-f","throtyl-9-1-f","throtyl-10-1-f",
        "throtyl-6-2-f","throtyl-7-2-f","throtyl-8-2-f",
        "throtyl-9-2-f","throtyl-10-2-f","throtyl-4-3-f",
        "throtyl-5-3-f","throtyl-7-3-f","throtyl-8-3-f",
        "throtyl-9-3-f","throtyl-10-3-f","throtyl-5-4-f",
        "throtyl-6-4-f","throtyl-7-4-f","throtyl-9-4-f" }));
    add_group("south_moors", ({
        "throtyl-10-7-m","throtyl-10-8-m","throtyl-10-9-m",
        "throtyl-10-10-m","throtyl-9-8-m","throtyl-9-9-m",
        "throtyl-9-10-m","throtyl-8-9-m","throtyl-8-10-m",
        "throtyl-11-8-m","throtyl-11-9-m","throtyl-12-9-m" }));
    add_group("north_moors", ({
        "throtyl-12-6-v","throtyl-12-7-m","throtyl-13-6-v",
        "throtyl-13-7-m","throtyl-13-8-m","throtyl-14-5-v",
        "throtyl-14-6-m","throtyl-14-7-m","throtyl-14-8-m",
        "throtyl-14-9-m","throtyl-15-5-m","throtyl-15-6-m",
        "throtyl-15-7-m","throtyl-15-8-m","throtyl-15-9-m" }));

    add_area_unit("forest", "hobgob", 30);
    add_area_unit("south_moors", "hobgob", 20);
    add_area_unit("north_moors", "moors_rider", 20);

}
