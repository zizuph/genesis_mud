//Room type {v}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C36_R23", ({0, "C37_R22", "C37_R23",
        "C37_R24", "C36_R24", "C35_R24", "C35_R23", 0}),
        ({"cedar", "beech", "balsam"}), ({"pond"}));
    }
