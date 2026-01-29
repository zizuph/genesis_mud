inherit "/d/Rhovanion/common/esgaroth/house.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-2-3", "south");
    set_extras("This is a small house in the northwestern section of " +
        "Esgaroth.  The owner appears to be a fisherman, and there are " +
        "various pieces of tackle lying around.\n");
    add_item("tackle", "This is hopelessly tangled fishing wire as well as " +
        "rusted hooks and broken poles.  The good tackle is probably kept " +
        "somewhere else, or in use at the moment.\n");
}
