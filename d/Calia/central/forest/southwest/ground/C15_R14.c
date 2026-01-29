//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C15_R14", ({"C15_R13", "C16_R13",
        "C16_R14", "C16_R15", "C15_R15", "C14_R15", "C14_R14", "C14_R13"}),
        ({"sycamore", "birch", "elm"}));
    }
