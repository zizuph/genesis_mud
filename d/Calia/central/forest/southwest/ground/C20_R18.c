//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C20_R18", ({"C20_R17", "C21_R17",
        "C21_R18", "C21_R19", "C20_R19", "C19_R19", "C19_R18", "C19_R17"}),
        ({"sycamore", "birch", "elm"}));
    }
