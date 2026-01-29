//Room type {/}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C29_R08", ({"C29_R07", "C30_R07",
        "C30_R08", "C30_R09", "C29_R09", "C28_R09", "C28_R08", "C28_R07"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northeast", "southwest"}));
    }
