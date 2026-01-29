//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C28_R07", ({"C28_R06", "C29_R06",
        "C29_R07", "C29_R08", "C28_R08", "C27_R08", "C27_R07", "C27_R06"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
