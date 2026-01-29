//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C31_R12", ({"C31_R11", "C32_R11",
        "C32_R12", "C32_R13", "C31_R13", "C30_R13", "C30_R12", "C30_R11"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
