//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C37_R15", ({"C37_R14", "C38_R14",
        "C38_R15", "C38_R16", "C37_R16", "C36_R16", "C36_R15", "C36_R14"}),
        ({"pine", "fir", "balsam", "spruce"}));
    }
