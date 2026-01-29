#include "/d/Shire/sys/defs.h"
#include "/d/Shire/sys/terrain.h"

inherit AREA_ROOM;

void create_misty() {}

void
create_area_room()
{
    set_land("Eriador");
    set_areatype(AREATYPE_ROCKY);
    set_areadesc("mountain path");
    set_areaname("the Misty Mountains");
    set_area("approching");
    set_no_herbs();

    create_misty();
}
