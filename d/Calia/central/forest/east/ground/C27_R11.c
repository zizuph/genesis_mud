//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C27_R11", ({"C27_R10", "C28_R10",
        "C28_R11", "C28_R12", "C27_R12", "C26_R12", "C26_R11", "C26_R10"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
