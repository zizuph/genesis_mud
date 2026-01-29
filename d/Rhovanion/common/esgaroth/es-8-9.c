inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-8-8", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-9-9", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-9-10", "southeast");
    add_exit("/d/Rhovanion/common/esgaroth/es-8-10", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-7-10", "southwest");
    set_extras("To the east is the city bank of Esgaroth, one of the " +
        "oldest buildings in town, and one of the most frequented by " +
        "visitors to the city.\n");
}
