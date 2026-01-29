//Room type {V}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C26_R25", ({"C26_R24", "C27_R24",
        "C27_R25", "C27_R26", "C26_R26", "C25_R26", "C25_R25", "C25_R24"}),
        ({"oak", "birch", "hickory"}), ({"west", "southeast"}));
    }
