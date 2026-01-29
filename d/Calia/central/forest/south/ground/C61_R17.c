//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C61_R17", ({"C61_R16", "C62_R16",
        "C62_R17", "C62_R18", "C61_R18", "C60_R18", "C60_R17", "C60_R16"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
