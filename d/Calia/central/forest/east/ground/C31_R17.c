//Room type {L}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C31_R17", ({0, "C32_R16", "C32_R17",
        "C32_R18", "C31_R18", "C30_R18", 0, 0}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northwest", "east"}));
    }
