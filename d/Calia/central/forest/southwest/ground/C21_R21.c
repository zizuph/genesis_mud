//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C21_R21", ({"C21_R20", "C22_R20",
        "C22_R21", "C22_R22", "C21_R22", "C20_R22", "C20_R21", "C20_R20"}),
        ({"sycamore", "birch", "elm"}));
    }
