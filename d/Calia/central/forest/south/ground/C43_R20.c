//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C43_R20", ({"C43_R19", "C44_R19",
        "C44_R20", "C44_R21", "C43_R21", "C42_R21", "C42_R20", "C42_R19"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
