//Room type {L}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C32_R16", ({0, "C33_R15", "C33_R16",
        "C33_R17", "C32_R17", "C31_R17", 0, 0}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northwest", "east"}));
    }
