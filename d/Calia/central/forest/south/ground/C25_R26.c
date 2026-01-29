//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C25_R26", ({"C25_R25", "C26_R25",
        "C26_R26", "C26_R27", "C25_R27", "C24_R27", "C24_R26", "C24_R25"}),
        ({"oak", "birch", "hickory"}));
    }
