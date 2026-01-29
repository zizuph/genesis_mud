//Room type {P}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C38_R32", ({"C38_R31", "C39_R31", 0, 0, 0,
        0, "C37_R32", "C37_R31"}),
        ({"cedar", "pine", "spruce", "fir"}), ({"southwest", "east"}));
    }
