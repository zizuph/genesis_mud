//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C16_R28", ({0, 0, "C17_R28", "C17_R29",
        "C16_R29", "C15_R29", "C15_R28", 0}),
        ({"spruce", "beech"}), ({"thicket"}));
    }
