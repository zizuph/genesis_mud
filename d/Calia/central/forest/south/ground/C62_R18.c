//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C62_R18", ({"C62_R17", "C63_R17", "C63_R18",
        0, 0, "C61_R19", "C61_R18", "C61_R17"}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
