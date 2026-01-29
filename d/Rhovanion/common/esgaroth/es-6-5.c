inherit "/d/Rhovanion/common/esgaroth/road.c";

create_exits()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-7-5", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-5-5", "west");
    set_extras("The market pool lies to the south, and you see " +
        "citizens of Esgaroth wandering by here, carrying buckets and " +
        "jugs of water and talking amongst themselves.\n");
}
