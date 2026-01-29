//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C62_R17", ({"C62_R16", "C63_R16",
        "C63_R17", "C63_R18", "C62_R18", "C61_R18", "C61_R17", "C61_R16"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
