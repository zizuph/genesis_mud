//Room type {v}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C34_R23", ({0, 0, "C35_R23", "C35_R24",
        "C34_R24", "C33_R24", "C33_R23", "C33_R22"}),
        ({"cedar", "beech", "balsam"}), ({"pond"}));
    }
