//Room type {/}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C28_R09", ({"C28_R08", "C29_R08",
        "C29_R09", "C29_R10", "C28_R10", "C27_R10", "C27_R09", "C27_R08"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northeast", "southwest"}));
    }
