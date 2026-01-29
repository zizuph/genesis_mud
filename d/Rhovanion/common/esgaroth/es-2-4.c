inherit "/d/Rhovanion/common/esgaroth/house.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-3-4", "east");
    set_extras("This house is run-down.  It seems the owner doesn't " +
        "take very good care of it.\n");
}
