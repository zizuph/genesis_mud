//Room type {L}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C33_R24", ({"C33_R23", "C34_R23",
        "C34_R24", "C34_R25", 0, 0, "C32_R24", "C32_R23"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northwest", "east"}));
    }
