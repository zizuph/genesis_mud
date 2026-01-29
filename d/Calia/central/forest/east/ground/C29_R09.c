//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C29_R09", ({"C29_R08", "C30_R08",
        "C30_R09", "C30_R10", "C29_R10", "C28_R10", "C28_R09", "C28_R08"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
