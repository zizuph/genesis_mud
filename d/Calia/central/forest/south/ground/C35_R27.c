//Room type {w}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C35_R27", ({"C35_R26", "C36_R26",
        "C36_R27", "C36_R28", "C35_R28", "C34_R28", "C34_R27", "C34_R26"}),
        ({"oak", "elm", "birch"}), 0, "northwest");
    }
