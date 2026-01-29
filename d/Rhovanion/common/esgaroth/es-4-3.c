inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-4-2", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-5-3", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-3-3", "west");
    set_extras("A house lies to the north, its front entrance cool and " +
        "shadowed.  To the south you hear the noise of a pub, but the " +
        "door doesn't seem to be on this side.\n");
}
