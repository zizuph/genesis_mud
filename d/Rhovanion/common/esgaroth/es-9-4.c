inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-9-3", "north");
    add_exit("/d/Rhovanion/common/esgaroth/es-10-4", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-9-5", "south");
    add_exit("/d/Rhovanion/common/esgaroth/es-8-4", "west");
    set_extras("To the east you hear the sounds(quietly though) of " +
        "glasses clinking and bottles knocking together.  There is a " +
        "sign above the door which reads: \"The Black Dragon\".  To the " +
        "west is another of the small homes of Esgaroth.\n");
}
