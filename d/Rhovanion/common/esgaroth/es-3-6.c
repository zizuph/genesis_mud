inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-4-6", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-2-7", "southwest");
    add_exit("/d/Rhovanion/common/esgaroth/es-2-6", "west");
    add_exit("/d/Rhovanion/common/esgaroth/es-2-5", "northwest");
    set_extras("The street branches off here to the northwest and " +
        "southwest, skirting a house which has an opening to the west.\n");
}
