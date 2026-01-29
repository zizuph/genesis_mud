//Room type {\}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C36_R25", ({"C36_R24", "C37_R24",
        "C37_R25", "C37_R26", "C36_R26", "C35_R26", "C35_R25", "C35_R24"}),
        ({"oak", "birch", "hickory"}), ({"northwest", "southeast"}));
    }
