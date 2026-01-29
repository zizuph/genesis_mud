//Room type {%}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C37_R24", ({"C37_R23", "C38_R23",
        "C38_R24", "C38_R25", "C37_R25", "C36_R25", "C36_R24", "C36_R23"}),
        ({"oak", "birch", "hickory"}), ({"west", "northeast"}));
    }
