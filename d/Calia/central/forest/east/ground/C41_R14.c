//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C41_R14", ({"C41_R13", "C42_R13",
        "C42_R14", "C42_R15", "C41_R15", "C40_R15", "C40_R14", "C40_R13"}),
        ({"pine", "fir", "balsam", "spruce"}));
    }
