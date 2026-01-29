//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C18_R20", ({"C18_R19", "C19_R19",
        "C19_R20", "C19_R21", "C18_R21", "C17_R21", "C17_R20", "C17_R19"}),
        ({"sycamore", "birch", "elm"}));
    }
