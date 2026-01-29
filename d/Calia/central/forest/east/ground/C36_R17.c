//Room type {v}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C36_R17", ({"C36_R16", "C37_R16", "C37_R17",
        0, 0, "C35_R18", "C35_R17", "C35_R16"}),
        ({"cedar", "beech", "balsam"}), ({"pond"}));
    }
