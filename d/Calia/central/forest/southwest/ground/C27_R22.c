//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C27_R22", ({"C27_R21", "C28_R21",
        "C28_R22", "C28_R23", "C27_R23", "C26_R23", "C26_R22", "C26_R21"}),
        ({"sycamore", "birch", "elm"}));
    }
