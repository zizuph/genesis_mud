//Room type {i}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C32_R11", ({"C32_R10", 0, "C33_R11",
        "C33_R12", "C32_R12", "C31_R12", "C31_R11", "C31_R10"}),
        ({"beech", "cedar", "birch"}), ({"mountains"}));
    }
