//Room type {-}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C26_R21", ({"C26_R20", "C27_R20",
        "C27_R21", "C27_R22", "C26_R22", "C25_R22", "C25_R21", "C25_R20"}),
        ({"sycamore", "birch", "elm"}), ({"west", "east"}));
    }
