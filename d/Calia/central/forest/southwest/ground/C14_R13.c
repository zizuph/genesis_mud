//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C14_R13", ({"C14_R12", "C15_R12",
        "C15_R13", "C15_R14", "C14_R14", "C13_R14", "C13_R13", "C13_R12"}),
        ({"sycamore", "birch", "elm"}));
    }
