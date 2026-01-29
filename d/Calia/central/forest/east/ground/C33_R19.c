//Room type {v}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C33_R19", ({"C33_R18", "C34_R18", "C34_R19",
        0, 0, 0, "C32_R19", "C32_R18"}),
        ({"cedar", "beech", "balsam"}), ({"pond"}));
    }
