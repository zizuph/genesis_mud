//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C13_R28", ({0, 0, "C14_R28", "C14_R29",
        "C13_R29", "C12_R29", "C12_R28", 0}),
        ({"spruce", "beech"}), ({"thicket"}));
    }
