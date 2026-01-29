//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C58_R15", ({0, "C59_R14", "C59_R15",
        "C59_R16", "C58_R16", "C57_R16", "C57_R15", 0}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
