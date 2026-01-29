//Room type {v}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C38_R22", ({0, "C39_R21", "C39_R22",
        "C39_R23", "C38_R23", "C37_R23", "C37_R22", 0}),
        ({"cedar", "beech", "balsam"}), ({"pond"}));
    }
