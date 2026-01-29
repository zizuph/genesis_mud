//Room type {v}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C60_R19", ({"C60_R18", "C61_R18", "C61_R19",
        0, 0, 0, "C59_R19", "C59_R18"}),
        ({"hickory", "oak", "elm"}), ({"thicket"}));
    }
