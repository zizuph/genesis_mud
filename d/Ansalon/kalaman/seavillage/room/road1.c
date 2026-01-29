#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/kalaman/seavillage/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit VILLAGE_ROAD;

void
reset_seavillage_room()
{
    return;
}

create_seavillage_room()
{
    set_short("A short way northeast of the harbour of Kalaman");
    set_long("@@long_descr");

    remove_item("kalaman");
    remove_item("city");
    remove_item("Kalaman");

    add_item(({"kalaman","city","Kalaman"}),"Kalaman lies "+
      "several miles south west of here.\n");
    add_item(({"breakwater","harbour"}),"A breakwater made out "+
      "of rocks and stones forms the harbour for the city "+
      "of Kalaman.\n");
    add_item(({"river","Vingaard river","vingaard river"}),
      "The mighty Vingaard River travels all the way to the "+
      "far off Vingaard Keep.\n");
    add_item(({"tower","beacon","beacon tower"}),
      "The great white beacon tower provides illumination for "+
      "ships at night, warning them of the rocks at the base of "+
      "the point.\n");

    add_exit(VILLAGEROOM + "road2","northeast",0,4);
    add_exit("/d/Ansalon/kalaman/room/path6","southwest",0,3);

    reset_seavillage_room();
}

string
long_descr()
{
    return tod_descr2() + "You are on a rocky path "+
    "on a cliff above the mouth of a bay, where the "+
    "mighty Vingaard River spills into the ocean. To the "+
    "south west lies a great white beacon tower and "+
    "the breakwater that forms the harbour for the city port "+
    "of Kalaman. To the northeast, the path follows the cliffs as "+
    "far as you can see. "+
    season_descr() + "\n";
}

