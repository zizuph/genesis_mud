//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C39_R21", ({"C39_R20", "C40_R20",
        "C40_R21", "C40_R22", "C39_R22", "C38_R22", "C38_R21", "C38_R20"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
