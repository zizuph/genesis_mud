//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C59_R15", ({"C59_R14", "C60_R14", "C60_R15",
        "C60_R16", "C59_R16", "C58_R16", "C58_R15", 0}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
