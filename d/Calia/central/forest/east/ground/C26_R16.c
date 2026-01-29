//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C26_R16", ({"C26_R15", "C27_R15",
        "C27_R16", "C27_R17", "C26_R17", "C25_R17", "C25_R16", "C25_R15"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
