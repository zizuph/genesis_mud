//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C09_R28", ({"C09_R27", 0, "C10_R28",
        "C10_R29", "C09_R29", "C08_R29", "C08_R28", "C08_R27"}),
        ({"spruce", "beech"}), ({"thicket"}));
    }
