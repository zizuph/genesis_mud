//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C39_R16", ({"C39_R15", "C40_R15",
        "C40_R16", "C40_R17", "C39_R17", "C38_R17", "C38_R16", "C38_R15"}),
        ({"pine", "fir", "balsam", "spruce"}));
    }
