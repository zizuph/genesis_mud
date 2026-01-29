//Room type {L}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C33_R15", ({0, "C34_R14", "C34_R15",
        "C34_R16", "C33_R16", "C32_R16", 0, 0}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northwest", "east"}));
    }
