//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C22_R19", ({"C22_R18", "C23_R18",
        "C23_R19", "C23_R20", "C22_R20", "C21_R20", "C21_R19", "C21_R18"}),
        ({"sycamore", "birch", "elm"}));
    }
