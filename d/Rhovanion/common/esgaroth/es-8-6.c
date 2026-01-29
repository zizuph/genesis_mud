inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-8-5", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-9-6", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-8-7", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-7-5", "northwest");
    set_extras("You can enter the great hall to the north or the east.  " +
        "To your west is the market pool.\n");
}
