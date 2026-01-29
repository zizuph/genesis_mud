//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C04_R28", ({"C04_R27", "C05_R27",
        "C05_R28", "C05_R29", "C04_R29", "C03_R29", "C03_R28", "C03_R27"}),
        ({"spruce", "balsam", "fir"}));
    }
