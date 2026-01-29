//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C41_R22", ({"C41_R21", "C42_R21",
        "C42_R22", "C42_R23", "C41_R23", "C40_R23", "C40_R22", "C40_R21"}),
        ({"pine", "fir", "balsam", "spruce"}));
    }
