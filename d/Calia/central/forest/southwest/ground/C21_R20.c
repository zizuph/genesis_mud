//Room type {W}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C21_R20", ({"C21_R19", "C22_R19",
        "C22_R20", "C22_R21", "C21_R21", "C20_R21", "C20_R20", "C20_R19"}),
        ({"sycamore", "birch", "elm"}), ({"northwest", "east"}));
    }
