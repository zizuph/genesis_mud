//Room type {e}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C08_R27", ({0, 0, "C09_R27", "C09_R28",
        "C08_R28", "C07_R28", "C07_R27", 0}),
        ({"spruce", "beech"}), ({"thicket"}));
    }
