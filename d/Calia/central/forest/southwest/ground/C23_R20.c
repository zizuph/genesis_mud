//Room type {-}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C23_R20", ({"C23_R19", "C24_R19",
        "C24_R20", "C24_R21", "C23_R21", "C22_R21", "C22_R20", "C22_R19"}),
        ({"sycamore", "birch", "elm"}), ({"west", "east"}));
    }
