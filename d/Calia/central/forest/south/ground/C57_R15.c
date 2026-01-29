//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C57_R15", ({0, 0, "C58_R15", "C58_R16",
        "C57_R16", "C56_R16", "C56_R15", 0}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
