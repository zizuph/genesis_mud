//Room type {L}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C30_R18", ({0, "C31_R17", "C31_R18",
        "C31_R19", "C30_R19", 0, 0, 0}),
        ({"cedar", "pine", "spruce", "fir"}), ({"northwest", "east"}));
    }
