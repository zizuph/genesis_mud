//Room type {%}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C26_R20", ({"C26_R19", "C27_R19",
        "C27_R20", "C27_R21", "C26_R21", "C25_R21", "C25_R20", "C25_R19"}),
        ({"sycamore", "birch", "elm"}), ({"west", "northeast"}));
    }
