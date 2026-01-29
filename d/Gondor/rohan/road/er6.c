#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";

#include "/d/Gondor/defs.h"

public void
create_roads()
{
    set_street("large, newly used, crosscountry road");
    set_where("north");
    set_county("Fenmark");
    set_land("Rohan");
    set_mountain("White Mountains");
    set_vegetation("juicy, light green grass");
    set_forest("Forest of Fear");
    set_extraline("The " +Vegetation+ " covers the north and "
           + "west horizon. South and east, a large forest called the "
           +Forest+ " makes your visual range very limited. The Western "
           + "turnpike is found to the northwest and is lost to the southeast. "
           + "If you look along the road to the southeast, you can see a "
           + "clearing.");

    add_exit(ROH_DIR + "road/er5", "northwest", 0);
    add_exit(ROH_DIR + "plains/c13", "north", 0,2);
    add_exit(ROH_DIR + "plains/b14", "east", 0,2);
    add_exit(ROH_DIR + "road/er7", "southeast", 0);
 
}
