//Room type {L}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C36_R24", ({"C36_R23", "C37_R23",
        "C37_R24", 0, "C36_R25", "C35_R25", "C35_R24", "C35_R23"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northwest", "east"}));
    }
