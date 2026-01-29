#pragma no_clone

inherit "/d/Krynn/std/placer";

#include "local.h"

void
create_placer()
{
    set_area_name("SouthernCourrain");
    set_base_path(S_COURRAIN);
    set_unit_path(LIVING);
    set_area_path(ROOM);

    add_group("balifor_bay", ({
        "s_courrain-3-17-h", "s_courrain-0-18-h", 
        "s_courrain-1-18-h", "s_courrain-2-18-h", 
        "s_courrain-3-18-h", "s_courrain-4-18-h", 
        "s_courrain-0-19-i", "s_courrain-1-19-h", 
        "s_courrain-2-19-h", "s_courrain-3-19-h", 
        "s_courrain-4-19-h", "s_courrain-5-19-h", 
        "s_courrain-6-19-h", "s_courrain-1-20-i", 
        "s_courrain-2-20-i", "s_courrain-3-20-i", 
        "s_courrain-4-20-i", "s_courrain-5-20-h",
        "s_courrain-5-21-i", "s_courrain-6-21-i" }));

    add_group("bloodsea", ({
        "s_courrain-16-0-B", "s_courrain-17-0-B", 
        "s_courrain-18-0-B", "s_courrain-16-1-B", 
        "s_courrain-17-1-B", "s_courrain-18-1-B", 
        "s_courrain-16-2-B", "s_courrain-17-2-B", 
        "s_courrain-18-2-B", "s_courrain-16-3-B", 
        "s_courrain-17-3-B", "s_courrain-18-3-B", 
        "s_courrain-16-4-B", "s_courrain-17-4-B", 
        "s_courrain-18-4-B", "s_courrain-16-5-B", 
        "s_courrain-17-5-B", "s_courrain-18-5-B", 
        "s_courrain-16-6-B", "s_courrain-17-6-B", 
        "s_courrain-18-6-B", "s_courrain-16-7-B", 
        "s_courrain-17-7-B", "s_courrain-18-7-B", 
        "s_courrain-16-8-B", "s_courrain-17-8-B", 
        "s_courrain-18-8-B", "s_courrain-16-9-B", 
        "s_courrain-17-9-B", "s_courrain-18-9-B", 
        "s_courrain-16-10-B", "s_courrain-17-10-B", 
        "s_courrain-18-10-B", "s_courrain-16-11-B", 
        "s_courrain-17-11-B", "s_courrain-18-11-B", 
        "s_courrain-16-12-B", "s_courrain-17-12-B", 
        "s_courrain-18-12-B", "s_courrain-14-12-B", 
        "s_courrain-15-12-B", "s_courrain-16-12-B", 
        "s_courrain-17-12-B", "s_courrain-18-12-B", 
        "s_courrain-19-12-B", "s_courrain-20-12-B", 
        "s_courrain-21-12-B" }));

    add_group("highsea", ({
        "s_courrain-19-15-s", "s_courrain-20-15-s",
        "s_courrain-21-15-s","s_courrain-22-15-s",
        "s_courrain-23-15-s","s_courrain-24-15-s",
        "s_courrain-25-15-y","s_courrain-19-16-s", 
        "s_courrain-20-16-s","s_courrain-21-16-s",
        "s_courrain-22-16-s","s_courrain-23-16-s",
        "s_courrain-24-16-s","s_courrain-25-16-y",
        "s_courrain-19-17-s", "s_courrain-20-17-s",
        "s_courrain-21-17-s","s_courrain-22-17-s",
        "s_courrain-23-17-s","s_courrain-24-17-s",
        "s_courrain-25-17-y","s_courrain-19-18-s", 
        "s_courrain-20-18-s","s_courrain-21-18-s",
        "s_courrain-22-18-s","s_courrain-23-18-s",
        "s_courrain-24-18-s","s_courrain-25-18-y", 
        "s_courrain-9-19-s", "s_courrain-10-19-s",
        "s_courrain-11-19-s","s_courrain-12-19-s",
        "s_courrain-13-19-s","s_courrain-19-19-s", 
        "s_courrain-20-19-s","s_courrain-21-19-s",
        "s_courrain-22-19-s","s_courrain-23-19-s",
        "s_courrain-24-19-s","s_courrain-25-19-s",
        "s_courrain-26-19-x","s_courrain-27-19-x",
        "s_courrain-28-19-y","s_courrain-6-20-s", 
        "s_courrain-7-20-s","s_courrain-8-20-s",
        "s_courrain-9-20-s", "s_courrain-10-20-s",
        "s_courrain-11-20-s","s_courrain-12-20-s",
        "s_courrain-13-20-s", "s_courrain-14-20-s", 
        "s_courrain-15-20-s","s_courrain-16-20-s",
        "s_courrain-17-20-s","s_courrain-18-20-s",
        "s_courrain-19-20-s", "s_courrain-20-20-s",
        "s_courrain-21-20-s","s_courrain-22-20-s",
        "s_courrain-23-20-s","s_courrain-24-20-s",
        "s_courrain-25-20-s","s_courrain-26-20-s",
        "s_courrain-27-20-s","s_courrain-28-20-y",
        "s_courrain-7-21-s","s_courrain-8-21-s",
        "s_courrain-9-21-s", "s_courrain-10-21-s",
        "s_courrain-11-21-s","s_courrain-12-21-s",
        "s_courrain-13-21-s", "s_courrain-14-21-s",
        "s_courrain-15-21-s","s_courrain-16-21-s",
        "s_courrain-17-21-s","s_courrain-18-21-s",
        "s_courrain-19-21-s", "s_courrain-20-21-s",
        "s_courrain-21-21-s","s_courrain-22-21-s",
        "s_courrain-23-21-s","s_courrain-24-21-s",
        "s_courrain-25-21-s","s_courrain-26-21-s",
        "s_courrain-27-21-s","s_courrain-28-21-y",
        "s_courrain-9-22-z", "s_courrain-10-22-z",
        "s_courrain-11-22-z","s_courrain-12-22-z",
        "s_courrain-13-22-z", "s_courrain-14-22-z",
        "s_courrain-15-22-z","s_courrain-16-22-z",
        "s_courrain-17-22-z","s_courrain-18-22-z",
        "s_courrain-19-22-z", "s_courrain-20-22-z",
        "s_courrain-21-22-z","s_courrain-22-22-z",
        "s_courrain-23-22-z","s_courrain-24-22-z",
        "s_courrain-25-22-z","s_courrain-26-22-z",
        "s_courrain-27-22-z","s_courrain-28-22-z" }));

    add_area_unit("balifor_bay", "balifor_merchant_schooner", 2);

    add_area_unit("bloodsea", "deep_sea_fishing_obj", 10);
    add_area_unit("bloodsea", "dark_shape", 8);
    add_area_unit("bloodsea", "balifor_merchant_schooner", 2);
    add_area_unit("bloodsea", "mino_raiding_ship", 3);

    add_area_unit("highsea", "deep_sea_fishing_obj", 25);
    add_area_unit("highsea", "courrain_water_shape", 12);
    add_area_unit("highsea", "mino_raiding_ship", 6);
}
