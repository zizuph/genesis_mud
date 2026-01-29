//Room type {i}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C32_R08", ({"C32_R07", 0, 0, 0, "C32_R09",
        "C31_R09", "C31_R08", "C31_R07"}),
        ({"beech", "cedar", "birch"}), ({"mountains"}));
    }
