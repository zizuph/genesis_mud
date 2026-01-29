//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C26_R22", ({"C26_R21", "C27_R21",
        "C27_R22", "C27_R23", "C26_R23", "C25_R23", "C25_R22", "C25_R21"}),
        ({"sycamore", "birch", "elm"}));
    }
