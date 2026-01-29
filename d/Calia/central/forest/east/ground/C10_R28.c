//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C10_R28", ({0, 0, "C11_R28", "C11_R29",
        "C10_R29", "C09_R29", "C09_R28", "C09_R27"}),
        ({"spruce", "beech"}), ({"thicket"}));
    }
