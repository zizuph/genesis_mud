//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C06_R28", ({"C06_R27", "C07_R27",
        "C07_R28", "C07_R29", "C06_R29", "C05_R29", "C05_R28", "C05_R27"}),
        ({"spruce", "balsam", "fir"}));
    }
