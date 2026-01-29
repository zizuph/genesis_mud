//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C63_R18", ({"C63_R17", "C64_R17", 0, 0, 0, 0,
        "C62_R18", "C62_R17"}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
