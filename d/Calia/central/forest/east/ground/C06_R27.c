//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C06_R27", ({0, 0, "C07_R27", "C07_R28",
        "C06_R28", "C05_R28", "C05_R27", 0}),
        ({"spruce", "beech"}), ({"thicket"}));
    }
