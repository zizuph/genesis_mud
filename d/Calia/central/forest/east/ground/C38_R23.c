//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C38_R23", ({"C38_R22", "C39_R22",
        "C39_R23", "C39_R24", "C38_R24", "C37_R24", "C37_R23", "C37_R22"}),
        ({"pine", "fir", "balsam", "spruce"}));
    }
