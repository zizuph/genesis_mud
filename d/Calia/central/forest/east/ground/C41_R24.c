//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C41_R24", ({"C41_R23", "C42_R23", "C42_R24",
        0, 0, 0, "C40_R24", "C40_R23"}),
        ({"cedar", "balsam", "fir", "beech"}), ({"mountains"}));
    }
