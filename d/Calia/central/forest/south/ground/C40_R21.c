//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C40_R21", ({"C40_R20", "C41_R20",
        "C41_R21", "C41_R22", "C40_R22", "C39_R22", "C39_R21", "C39_R20"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
