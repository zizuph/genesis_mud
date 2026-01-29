//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C14_R28", ({0, 0, "C15_R28", "C15_R29",
        "C14_R29", "C13_R29", "C13_R28", 0}),
        ({"spruce", "beech"}), ({"thicket"}));
    }
