//Room type {W}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C27_R26", ({"C27_R25", "C28_R25",
        "C28_R26", "C28_R27", "C27_R27", "C26_R27", "C26_R26", "C26_R25"}),
        ({"oak", "birch", "hickory"}), ({"northwest", "east"}));
    }
