//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C26_R11", ({"C26_R10", "C27_R10",
        "C27_R11", "C27_R12", "C26_R12", "C25_R12", "C25_R11", "C25_R10"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
