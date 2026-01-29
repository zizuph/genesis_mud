//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C42_R23", ({"C42_R22", 0, 0, 0, "C42_R24",
        "C41_R24", "C41_R23", "C41_R22"}),
        ({"cedar", "balsam", "fir", "beech"}), ({"mountains"}));
    }
