//Room type {v}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C40_R18", ({"C40_R17", "C41_R17", "C41_R18",
        "C41_R19", "C40_R19", 0, 0, "C39_R17"}),
        ({"cedar", "beech", "balsam"}), ({"pond"}));
    }
