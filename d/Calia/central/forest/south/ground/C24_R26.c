//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C24_R26", ({"C24_R25", "C25_R25",
        "C25_R26", "C25_R27", "C24_R27", "C23_R27", "C23_R26", "C23_R25"}),
        ({"oak", "birch", "hickory"}));
    }
