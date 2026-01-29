//Room type {W}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C37_R26", ({"C37_R25", "C38_R25",
        "C38_R26", "C38_R27", "C37_R27", "C36_R27", "C36_R26", "C36_R25"}),
        ({"oak", "birch", "hickory"}), ({"northwest", "east"}));
    }
