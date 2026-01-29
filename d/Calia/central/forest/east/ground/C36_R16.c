//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C36_R16", ({"C36_R15", "C37_R15",
        "C37_R16", "C37_R17", "C36_R17", "C35_R17", "C35_R16", "C35_R15"}),
        ({"pine", "fir", "balsam", "spruce"}));
    }
