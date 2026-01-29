//Room type {L}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C31_R21", ({0, 0, "C32_R21", "C32_R22",
        "C31_R22", 0, 0, 0}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northwest", "east"}));
    }
