//Room type {L}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C34_R25", ({"C34_R24", "C35_R24",
        "C35_R25", "C35_R26", 0, 0, 0, "C33_R24"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northwest", "east"}));
    }
