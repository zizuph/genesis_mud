//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C25_R18", ({"C25_R17", "C26_R17",
        "C26_R18", "C26_R19", "C25_R19", "C24_R19", "C24_R18", "C24_R17"}),
        ({"sycamore", "birch", "elm"}));
    }
