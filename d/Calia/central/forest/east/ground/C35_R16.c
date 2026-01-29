//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C35_R16", ({"C35_R15", "C36_R15",
        "C36_R16", "C36_R17", "C35_R17", "C34_R17", "C34_R16", "C34_R15"}),
        ({"pine", "fir", "balsam", "spruce"}));
    }
