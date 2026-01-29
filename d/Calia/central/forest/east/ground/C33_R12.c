//Room type {i}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C33_R12", ({"C33_R11", 0, 0, 0, 0, "C32_R13",
        "C32_R12", "C32_R11"}),
        ({"beech", "cedar", "birch"}), ({"mountains"}));
    }
