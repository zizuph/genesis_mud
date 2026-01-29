//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C26_R09", ({"C26_R08", "C27_R08",
        "C27_R09", "C27_R10", "C26_R10", "C25_R10", "C25_R09", "C25_R08"}),
        ({"cedar", "beech", "balsam", "fir"}));
    }
