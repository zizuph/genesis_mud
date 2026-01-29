//Room type {-}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C25_R20", ({"C25_R19", "C26_R19",
        "C26_R20", "C26_R21", "C25_R21", "C24_R21", "C24_R20", "C24_R19"}),
        ({"sycamore", "birch", "elm"}), ({"west", "east"}));
    }
