//Room type {L}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C39_R24", ({"C39_R23", "C40_R23",
        "C40_R24", 0, 0, 0, "C38_R24", "C38_R23"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northwest", "east"}));
    }
