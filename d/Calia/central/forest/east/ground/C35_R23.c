//Room type {v}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C35_R23", ({0, 0, "C36_R23", "C36_R24",
        "C35_R24", "C34_R24", "C34_R23", 0}),
        ({"cedar", "beech", "balsam"}), ({"pond"}));
    }
