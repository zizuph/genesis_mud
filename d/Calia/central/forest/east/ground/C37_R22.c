//Room type {v}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C37_R22", ({0, 0, "C38_R22", "C38_R23",
        "C37_R23", "C36_R23", 0, 0}),
        ({"cedar", "beech", "balsam"}), ({"pond"}));
    }
