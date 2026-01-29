//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C26_R14", ({"C26_R13", "C27_R13",
        "C27_R14", "C27_R15", "C26_R15", "C25_R15", "C25_R14", "C25_R13"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
