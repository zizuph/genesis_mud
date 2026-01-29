//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C63_R13", ({"C63_R12", "C64_R12", "C64_R13",
        "C64_R14", "C63_R14", "C62_R14", "C62_R13", 0}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
