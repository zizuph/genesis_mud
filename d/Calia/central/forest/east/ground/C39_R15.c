//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C39_R15", ({"C39_R14", "C40_R14",
        "C40_R15", "C40_R16", "C39_R16", "C38_R16", "C38_R15", "C38_R14"}),
        ({"pine", "fir", "balsam", "spruce"}));
    }
