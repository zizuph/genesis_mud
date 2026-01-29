//Room type {m}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C40_R24", ({"C40_R23", "C41_R23", "C41_R24",
        0, 0, 0, "C39_R24", "C39_R23"}),
        ({"cedar", "balsam", "fir", "beech"}), ({"mountains"}));
    }
