//Room type {W}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C14_R25", ({"C14_R24", "C15_R24",
        "C15_R25", "C15_R26", "C14_R26", "C13_R26", "C13_R25", "C13_R24"}),
        ({"oak", "birch", "hickory"}), ({"northwest", "east"}));
    }
