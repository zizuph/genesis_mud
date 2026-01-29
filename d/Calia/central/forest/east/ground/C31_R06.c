//Room type {i}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C31_R06", ({"C31_R05", "C32_R05", "C32_R06",
        "C32_R07", "C31_R07", "C30_R07", "C30_R06", "C30_R05"}),
        ({"beech", "cedar", "birch"}), ({"mountains"}));
    }
