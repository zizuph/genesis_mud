//Room type {v}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C40_R19", ({"C40_R18", "C41_R18", "C41_R19",
        "C41_R20", "C40_R20", 0, 0, 0}),
        ({"cedar", "beech", "balsam"}), ({"pond"}));
    }
