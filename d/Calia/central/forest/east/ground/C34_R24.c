//Room type {L}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C34_R24", ({"C34_R23", "C35_R23",
        "C35_R24", "C35_R25", "C34_R25", 0, "C33_R24", "C33_R23"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northwest", "east"}));
    }
