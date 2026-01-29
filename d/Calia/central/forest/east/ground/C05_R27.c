//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C05_R27", ({0, 0, "C06_R27", "C06_R28",
        "C05_R28", "C04_R28", "C04_R27", 0}),
        ({"spruce", "beech"}), ({"thicket"}));
    }
