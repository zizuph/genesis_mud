//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C68_R14", ({"C68_R13", 0, 0, 0, "C68_R15",
        "C67_R15", "C67_R14", "C67_R13"}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
