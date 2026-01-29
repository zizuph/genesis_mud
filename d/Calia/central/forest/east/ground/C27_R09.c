//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C27_R09", ({"C27_R08", "C28_R08",
        "C28_R09", "C28_R10", "C27_R10", "C26_R10", "C26_R09", "C26_R08"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
