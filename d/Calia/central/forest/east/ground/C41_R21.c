//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C41_R21", ({"C41_R20", "C42_R20",
        "C42_R21", "C42_R22", "C41_R22", "C40_R22", "C40_R21", "C40_R20"}),
        ({"pine", "fir", "balsam", "spruce"}));
    }
