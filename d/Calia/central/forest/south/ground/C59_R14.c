//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C59_R14", ({0, 0, "C60_R14", "C60_R15",
        "C59_R15", "C58_R15", 0, 0}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
