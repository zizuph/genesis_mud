//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C20_R17", ({"C20_R16", "C21_R16",
        "C21_R17", "C21_R18", "C20_R18", "C19_R18", "C19_R17", "C19_R16"}),
        ({"sycamore", "birch", "elm"}));
    }
