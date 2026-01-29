//Room type {g}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C12_R31", ({"C12_R30", "C13_R30", "C13_R31",
        "C13_R32", "C12_R32", 0, "C11_R31", "C11_R30"}),
        ({"spruce"}), ({"mountains"}));
    }
