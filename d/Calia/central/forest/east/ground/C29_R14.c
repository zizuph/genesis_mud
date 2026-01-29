//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C29_R14", ({"C29_R13", "C30_R13",
        "C30_R14", "C30_R15", "C29_R15", "C28_R15", "C28_R14", "C28_R13"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
