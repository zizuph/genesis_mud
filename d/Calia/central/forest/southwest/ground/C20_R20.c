//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C20_R20", ({"C20_R19", "C21_R19",
        "C21_R20", "C21_R21", "C20_R21", "C19_R21", "C19_R20", "C19_R19"}),
        ({"sycamore", "birch", "elm"}));
    }
