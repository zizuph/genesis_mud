//Room type {-}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C32_R03", ({"C32_R02", "C33_R02",
        "C33_R03", "C33_R04", "C32_R04", "C31_R04", "C31_R03", "C31_R02"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"east", "west"}));
    }
