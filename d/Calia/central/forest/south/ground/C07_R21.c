//Room type {C}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C07_R21", ({"C07_R20", "C08_R20",
        "C08_R21", "C08_R22", "C07_R22", "C06_R22", "C06_R21", "C06_R20"}),
        ({"oak", "sycamore", "birch", "elm"}), ({"southeast", "northwest"}));
    }
