//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C22_R16", ({"C22_R15", "C23_R15",
        "C23_R16", "C23_R17", "C22_R17", "C21_R17", "C21_R16", "C21_R15"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
