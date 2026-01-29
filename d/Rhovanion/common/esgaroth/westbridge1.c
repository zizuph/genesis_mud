inherit "/d/Rhovanion/lib/room";

create_room()
{
    set_short("Bridge to Esgaroth");
    set_long("This bridge leads over deep, still water into the lake town " +
        "of Esgaroth, and continues to the west where it turns into a " +
        "path which enters Mirkwood.\n");
    add_exit("/d/Rhovanion/common/esgaroth/es-1-11", "east");
    add_exit("/d/Rhovanion/common/esgaroth/westbridge2", "west");
}
