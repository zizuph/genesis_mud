//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C17_R31", ({"C17_R30", "C18_R30",
        "C18_R31", "C18_R32", "C17_R32", "C16_R32", "C16_R31", "C16_R30"}),
        ({"spruce", "balsam", "fir"}));
    }
