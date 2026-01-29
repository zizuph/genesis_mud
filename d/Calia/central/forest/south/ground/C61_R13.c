//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C61_R13", ({0, 0, "C62_R13", "C62_R14",
        "C61_R14", "C60_R14", 0, 0}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
