//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C31_R08", ({"C31_R07", "C32_R07",
        "C32_R08", "C32_R09", "C31_R09", "C30_R09", "C30_R08", "C30_R07"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
