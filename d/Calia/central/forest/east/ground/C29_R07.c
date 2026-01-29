//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C29_R07", ({"C29_R06", "C30_R06",
        "C30_R07", "C30_R08", "C29_R08", "C28_R08", "C28_R07", "C28_R06"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
