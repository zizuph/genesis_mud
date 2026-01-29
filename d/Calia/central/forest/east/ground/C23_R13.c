//Room type {/}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C23_R13", ({"C23_R12", "C24_R12",
        "C24_R13", "C24_R14", "C23_R14", "C22_R14", "C22_R13", "C22_R12"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northeast", "southwest"}));
    }
