//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C29_R21", ({"C29_R20", "C30_R20",
        "C30_R21", "C30_R22", "C29_R22", "C28_R22", "C28_R21", "C28_R20"}),
        ({"sycamore", "birch", "elm"}));
    }
