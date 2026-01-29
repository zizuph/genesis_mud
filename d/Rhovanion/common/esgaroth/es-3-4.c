inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-3-3", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-4-4", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-4-5", "southeast");
    add_exit("/d/Rhovanion/common/esgaroth/es-2-5", "southwest");
    add_exit("/d/Rhovanion/common/esgaroth/es-2-4", "west");
    set_extras("To the east you see a sign over the doorway which reads: " +
        "\"The Golden Claw\".  To the west is a house.\n"); 
}
