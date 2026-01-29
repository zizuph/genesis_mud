//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C02_R28", ({0, "C03_R27", "C03_R28",
        "C03_R29", 0, 0, "C01_R28", 0}),
        ({"spruce", "beech"}), ({"thicket"}));
    }
