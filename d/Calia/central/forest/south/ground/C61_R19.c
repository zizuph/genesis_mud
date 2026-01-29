//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C61_R19", ({"C61_R18", "C62_R18", 0, 0, 0, 0,
        "C60_R19", "C60_R18"}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
