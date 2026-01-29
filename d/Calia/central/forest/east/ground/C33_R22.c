//Room type {v}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C33_R22", ({0, 0, 0, "C34_R23", "C33_R23",
        "C32_R23", "C32_R22", "C32_R21"}),
        ({"cedar", "beech", "balsam"}), ({"pond"}));
    }
