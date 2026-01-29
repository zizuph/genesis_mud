//Room type {v}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C39_R22", ({"C39_R21", "C40_R21", "C40_R22",
        "C40_R23", "C39_R23", "C38_R23", "C38_R22", 0}),
        ({"cedar", "beech", "balsam"}), ({"pond"}));
    }
