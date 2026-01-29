//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C24_R15", ({"C24_R14", "C25_R14",
        "C25_R15", "C25_R16", "C24_R16", "C23_R16", "C23_R15", "C23_R14"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
