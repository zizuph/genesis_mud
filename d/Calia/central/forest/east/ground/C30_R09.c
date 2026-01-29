//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C30_R09", ({"C30_R08", "C31_R08",
        "C31_R09", "C31_R10", "C30_R10", "C29_R10", "C29_R09", "C29_R08"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
