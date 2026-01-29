//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C68_R15", ({"C68_R14", 0, 0, 0, 0, "C67_R16",
        "C67_R15", "C67_R14"}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
