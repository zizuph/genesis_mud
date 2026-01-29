//Room type {/}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C24_R12", ({"C24_R11", "C25_R11",
        "C25_R12", "C25_R13", "C24_R13", "C23_R13", "C23_R12", "C23_R11"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northeast", "southwest"}));
    }
