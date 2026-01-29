//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C25_R22", ({"C25_R21", "C26_R21",
        "C26_R22", "C26_R23", "C25_R23", "C24_R23", "C24_R22", "C24_R21"}),
        ({"sycamore", "birch", "elm"}));
    }
