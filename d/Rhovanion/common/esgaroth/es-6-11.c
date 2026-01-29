inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-6-10", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-6-12", "south");
    set_extras("To the south lies the visitor's center of Esgaroth, " +
        "where the people of the city hope to attract visitors, and " +
        "where they hope those visitors will spend their money.\n");
}
