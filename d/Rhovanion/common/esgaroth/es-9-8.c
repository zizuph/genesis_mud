inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-10-7", "northeast");
    add_exit("/d/Rhovanion/common/esgaroth/es-10-8", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-10-9", "southeast");
    add_exit("/d/Rhovanion/common/esgaroth/es-8-8", "west");
    set_extras("To the east is the town's inn, where visitors can stay " +
        "the night in comfort and safety.\n");
}
