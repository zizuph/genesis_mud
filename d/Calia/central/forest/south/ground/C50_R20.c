//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C50_R20", ({"C50_R19", "C51_R19",
        "C51_R20", "C51_R21", "C50_R21", "C49_R21", "C49_R20", "C49_R19"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
