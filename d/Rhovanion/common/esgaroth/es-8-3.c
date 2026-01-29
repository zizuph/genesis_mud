inherit "/d/Rhovanion/common/esgaroth/house.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-8-2", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-9-3", "east");
    set_extras("To the north is the main entrance, and east is a side " +
        "exit.\n");
}
