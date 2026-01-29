//Room type {'}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C27_R10", ({"C27_R09", "C28_R09",
        "C28_R10", "C28_R11", "C27_R11", "C26_R11", "C26_R10", "C26_R09"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"west", "northeast"}));
    }
