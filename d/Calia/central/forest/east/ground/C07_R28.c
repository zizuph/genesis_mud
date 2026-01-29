//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C07_R28", ({"C07_R27", "C08_R27",
        "C08_R28", "C08_R29", "C07_R29", "C06_R29", "C06_R28", "C06_R27"}),
        ({"spruce", "balsam", "fir"}));
    }
