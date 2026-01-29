//Room type {v}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C33_R23", ({"C33_R22", 0, "C34_R23",
        "C34_R24", "C33_R24", "C32_R24", "C32_R23", "C32_R22"}),
        ({"cedar", "beech", "balsam"}), ({"pond"}));
    }
