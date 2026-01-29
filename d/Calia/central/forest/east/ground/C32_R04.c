//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C32_R04", ({"C32_R03", "C33_R03",
        "C33_R04", "C33_R05", "C32_R05", "C31_R05", "C31_R04", "C31_R03"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
