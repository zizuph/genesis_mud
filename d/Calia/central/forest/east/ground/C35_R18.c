//Room type {v}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C35_R18", ({"C35_R17", "C36_R17", 0, 0, 0,
        "C34_R19", "C34_R18", "C34_R17"}),
        ({"cedar", "beech", "balsam"}), ({"pond"}));
    }
