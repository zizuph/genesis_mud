inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-7-13", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-5-13", "west");
add_exit("/d/Rhovanion/common/rhun/river/esg_pier","south");
    set_extras("The road extends to the south, where it forms a pier " +
        "for ships to dock at.\n");
}
