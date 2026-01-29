//Room type {L}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C32_R23", ({"C32_R22", "C33_R22",
        "C33_R23", "C33_R24", "C32_R24", 0, "C31_R23", "C31_R22"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northwest", "east"}));
    }
