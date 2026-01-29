inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-2-1", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-1-2", "south");
    set_extras("This is the northwest corner of the city.  Looking far " +
        "to the northeast, you see the lonely mountain.\n");
}
