//Room type {V}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C40_R26", ({"C40_R25", "C41_R25",
        "C41_R26", "C41_R27", "C40_R27", "C39_R27", "C39_R26", "C39_R25"}),
        ({"oak", "birch", "hickory"}), ({"west", "southeast"}));
    }
