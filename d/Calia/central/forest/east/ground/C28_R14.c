//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C28_R14", ({"C28_R13", "C29_R13",
        "C29_R14", "C29_R15", "C28_R15", "C27_R15", "C27_R14", "C27_R13"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
