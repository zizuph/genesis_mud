//Room type {y}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C60_R17", ({"C60_R16", "C61_R16",
        "C61_R17", "C61_R18", "C60_R18", "C59_R18", "C59_R17", "C59_R16"}),
        ({"oak", "sycamore", "birch", "elm"}));
    }
