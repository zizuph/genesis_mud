//Room type {v}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C57_R19", ({"C57_R18", "C58_R18", "C58_R19",
        0, 0, 0, "C56_R19", "C56_R18"}),
        ({"hickory", "oak", "elm"}), ({"thicket"}));
    }
