//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C43_R20", ({"C43_R19", "C44_R19", 0, 0, 0,
        "C42_R21", "C42_R20", "C42_R19"}),
        ({"cedar", "balsam", "fir", "beech"}), ({"mountains"}));
    }
