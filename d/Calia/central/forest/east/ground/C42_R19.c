//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C42_R19", ({"C42_R18", "C43_R18",
        "C43_R19", "C43_R20", "C42_R20", "C41_R20", "C41_R19", "C41_R18"}),
        ({"pine", "fir", "balsam", "spruce"}));
    }
