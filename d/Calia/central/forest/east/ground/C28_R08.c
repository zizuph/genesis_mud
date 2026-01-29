//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C28_R08", ({"C28_R07", "C29_R07",
        "C29_R08", "C29_R09", "C28_R09", "C27_R09", "C27_R08", "C27_R07"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
