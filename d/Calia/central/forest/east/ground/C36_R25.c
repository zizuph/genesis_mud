//Room type {L}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C36_R25", ({"C36_R24", "C37_R24", 0, 0, 0,
        "C35_R26", "C35_R25", "C35_R24"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northwest", "east"}));
    }
