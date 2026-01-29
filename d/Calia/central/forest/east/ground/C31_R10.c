//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C31_R10", ({"C31_R09", "C32_R09",
        "C32_R10", "C32_R11", "C31_R11", "C30_R11", "C30_R10", "C30_R09"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
