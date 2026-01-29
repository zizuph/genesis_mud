//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C37_R21", ({"C37_R20", "C38_R20",
        "C38_R21", "C38_R22", "C37_R22", "C36_R22", "C36_R21", "C36_R20"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
