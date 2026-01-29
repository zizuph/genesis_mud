//Room type {w}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C26_R27", ({"C26_R26", "C27_R26",
        "C27_R27", "C27_R28", "C26_R28", "C25_R28", "C25_R27", "C25_R26"}),
        ({"oak", "elm", "birch"}), 0, "northwest");
    }
