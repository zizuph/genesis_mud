inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-11-2", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-10-1", "west");
    set_extras("This is the northeast corner of Esgaroth, looking off " +
        "into the distance you can see the lonely mountain, and to your " +
        "east lies the lake.\n");
    add_item("lake", "The water of the lake is dark and clear.\n");
}
