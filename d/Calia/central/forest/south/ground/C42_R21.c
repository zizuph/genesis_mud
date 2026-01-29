//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C42_R21", ({"C42_R20", "C43_R20",
        "C43_R21", "C43_R22", "C42_R22", "C41_R22", "C41_R21", "C41_R20"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
