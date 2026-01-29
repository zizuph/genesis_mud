//Room type {/}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C25_R11", ({"C25_R10", "C26_R10",
        "C26_R11", "C26_R12", "C25_R12", "C24_R12", "C24_R11", "C24_R10"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northeast", "southwest"}));
    }
