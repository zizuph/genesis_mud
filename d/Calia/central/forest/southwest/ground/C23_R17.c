//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C23_R17", ({"C23_R16", "C24_R16",
        "C24_R17", "C24_R18", "C23_R18", "C22_R18", "C22_R17", "C22_R16"}),
        ({"sycamore", "birch", "elm"}));
    }
