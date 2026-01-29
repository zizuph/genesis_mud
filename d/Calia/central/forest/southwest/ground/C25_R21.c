//Room type {W}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C25_R21", ({"C25_R20", "C26_R20",
        "C26_R21", "C26_R22", "C25_R22", "C24_R22", "C24_R21", "C24_R20"}),
        ({"sycamore", "birch", "elm"}), ({"northwest", "east"}));
    }
