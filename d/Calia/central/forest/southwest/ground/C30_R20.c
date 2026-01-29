//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C30_R20", ({"C30_R19", "C31_R19",
        "C31_R20", "C31_R21", "C30_R21", "C29_R21", "C29_R20", "C29_R19"}),
        ({"sycamore", "birch", "elm"}));
    }
