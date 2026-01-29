//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C04_R27", ({0, 0, "C05_R27", "C05_R28",
        "C04_R28", "C03_R28", "C03_R27", 0}),
        ({"spruce", "beech"}), ({"thicket"}));
    }
