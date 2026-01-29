//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C38_R21", ({"C38_R20", "C39_R20",
        "C39_R21", "C39_R22", "C38_R22", "C37_R22", "C37_R21", "C37_R20"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
