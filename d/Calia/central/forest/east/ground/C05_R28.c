//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C05_R28", ({"C05_R27", "C06_R27",
        "C06_R28", "C06_R29", "C05_R29", "C04_R29", "C04_R28", "C04_R27"}),
        ({"spruce", "balsam", "fir"}));
    }
