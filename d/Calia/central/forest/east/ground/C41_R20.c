//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C41_R20", ({"C41_R19", "C42_R19",
        "C42_R20", "C42_R21", "C41_R21", "C40_R21", "C40_R20", "C40_R19"}),
        ({"pine", "fir", "balsam", "spruce"}));
    }
