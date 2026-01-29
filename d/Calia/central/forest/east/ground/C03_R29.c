//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C03_R29", ({"C03_R28", "C04_R28", "C04_R29",
        "C04_R30", "C03_R30", 0, 0, "C02_R28"}),
        ({"spruce", "beech"}), ({"thicket"}));
    }
