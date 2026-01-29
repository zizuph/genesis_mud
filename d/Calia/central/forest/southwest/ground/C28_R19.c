//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C28_R19", ({"C28_R18", "C29_R18",
        "C29_R19", "C29_R20", "C28_R20", "C27_R20", "C27_R19", "C27_R18"}),
        ({"sycamore", "birch", "elm"}));
    }
