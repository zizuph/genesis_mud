//Room type {i}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C32_R06", ({"C32_R05", "C33_R05", 0, 0,
        "C32_R07", "C31_R07", "C31_R06", "C31_R05"}),
        ({"beech", "cedar", "birch"}), ({"mountains"}));
    }
