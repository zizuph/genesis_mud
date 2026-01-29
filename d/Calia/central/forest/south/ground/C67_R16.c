//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C67_R16", ({"C67_R15", "C68_R15", 0, 0, 0,
        "C66_R17", "C66_R16", "C66_R15"}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
