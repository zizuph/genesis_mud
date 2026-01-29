//Room type {%}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C30_R26", ({"C30_R25", "C31_R25",
        "C31_R26", "C31_R27", "C30_R27", "C29_R27", "C29_R26", "C29_R25"}),
        ({"oak", "birch", "hickory"}), ({"west", "northeast"}));
    }
