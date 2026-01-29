inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-7-4", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-8-6", "southeast");
    add_exit("/d/Rhovanion/common/esgaroth/es-6-5", "west");
    set_extras("The great hall rises up to the east, easily the tallest " +
        "building in the low-slung city of Esgaroth.\n");
}
