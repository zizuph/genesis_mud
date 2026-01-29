//Room type {L}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C35_R26", ({"C35_R25", "C36_R25", 0, 0,
        "C35_R27", 0, 0, "C34_R25"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northwest", "east"}));
    }
