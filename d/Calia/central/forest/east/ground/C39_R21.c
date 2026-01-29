//Room type {v}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C39_R21", ({0, "C40_R20", "C40_R21",
        "C40_R22", "C39_R22", "C38_R22", 0, 0}),
        ({"cedar", "beech", "balsam"}), ({"pond"}));
    }
