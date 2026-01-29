//Room type {w}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C37_R27", ({"C37_R26", "C38_R26",
        "C38_R27", "C38_R28", "C37_R28", "C36_R28", "C36_R27", "C36_R26"}),
        ({"oak", "elm", "birch"}), 0, "northwest");
    }
