//Room type {V}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C28_R21", ({"C28_R20", "C29_R20",
        "C29_R21", "C29_R22", "C28_R22", "C27_R22", "C27_R21", "C27_R20"}),
        ({"sycamore", "birch", "elm"}), ({"west", "southeast"}));
    }
