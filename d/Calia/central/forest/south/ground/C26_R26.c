//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C26_R26", ({"C26_R25", "C27_R25",
        "C27_R26", "C27_R27", "C26_R27", "C25_R27", "C25_R26", "C25_R25"}),
        ({"oak", "birch", "hickory"}));
    }
