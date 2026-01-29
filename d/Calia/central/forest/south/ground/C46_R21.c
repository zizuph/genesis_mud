//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C46_R21", ({"C46_R20", "C47_R20",
        "C47_R21", "C47_R22", "C46_R22", "C45_R22", "C45_R21", "C45_R20"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
