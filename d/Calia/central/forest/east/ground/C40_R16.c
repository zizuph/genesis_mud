//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C40_R16", ({"C40_R15", "C41_R15",
        "C41_R16", "C41_R17", "C40_R17", "C39_R17", "C39_R16", "C39_R15"}),
        ({"pine", "fir", "balsam", "spruce"}));
    }
