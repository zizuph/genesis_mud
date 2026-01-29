//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C60_R14", ({0, "C61_R13", "C61_R14",
        "C61_R15", "C60_R15", "C59_R15", "C59_R14", 0}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
