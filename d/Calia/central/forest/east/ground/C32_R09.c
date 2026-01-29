//Room type {i}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C32_R09", ({"C32_R08", 0, 0, 0, "C32_R10",
        "C31_R10", "C31_R09", "C31_R08"}),
        ({"beech", "cedar", "birch"}), ({"mountains"}));
    }
