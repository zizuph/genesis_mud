//Room type {w}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C40_R28", ({"C40_R27", "C41_R27",
        "C41_R28", "C41_R29", "C40_R29", "C39_R29", "C39_R28", "C39_R27"}),
        ({"oak", "elm", "birch"}), 0, "northwest");
    }
