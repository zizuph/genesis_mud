//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C26_R12", ({"C26_R11", "C27_R11",
        "C27_R12", "C27_R13", "C26_R13", "C25_R13", "C25_R12", "C25_R11"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
