//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C29_R20", ({"C29_R19", "C30_R19",
        "C30_R20", "C30_R21", "C29_R21", "C28_R21", "C28_R20", "C28_R19"}),
        ({"sycamore", "birch", "elm"}));
    }
