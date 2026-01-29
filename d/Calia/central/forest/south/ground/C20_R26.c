//Room type {z}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C20_R26", ({"C20_R25", "C21_R25",
        "C21_R26", "C21_R27", "C20_R27", "C19_R27", "C19_R26", "C19_R25"}),
        ({"oak", "birch", "hickory"}));
    }
