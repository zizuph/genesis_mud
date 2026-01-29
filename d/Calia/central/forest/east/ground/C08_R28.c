//Room type {d}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C08_R28", ({"C08_R27", "C09_R27",
        "C09_R28", "C09_R29", "C08_R29", "C07_R29", "C07_R28", "C07_R27"}),
        ({"spruce", "balsam", "fir"}));
    }
