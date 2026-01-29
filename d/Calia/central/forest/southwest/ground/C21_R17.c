//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C21_R17", ({"C21_R16", "C22_R16",
        "C22_R17", "C22_R18", "C21_R18", "C20_R18", "C20_R17", "C20_R16"}),
        ({"sycamore", "birch", "elm"}));
    }
