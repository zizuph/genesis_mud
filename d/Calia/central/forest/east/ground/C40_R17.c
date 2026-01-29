//Room type {v}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C40_R17", ({"C40_R16", "C41_R16", "C41_R17",
        "C41_R18", "C40_R18", 0, "C39_R17", "C39_R16"}),
        ({"cedar", "beech", "balsam"}), ({"pond"}));
    }
