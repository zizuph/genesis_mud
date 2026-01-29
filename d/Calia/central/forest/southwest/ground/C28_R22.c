//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C28_R22", ({"C28_R21", "C29_R21",
        "C29_R22", "C29_R23", "C28_R23", "C27_R23", "C27_R22", "C27_R21"}),
        ({"sycamore", "birch", "elm"}));
    }
