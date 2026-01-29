//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C17_R17", ({"C17_R16", "C18_R16",
        "C18_R17", "C18_R18", "C17_R18", "C16_R18", "C16_R17", "C16_R16"}),
        ({"sycamore", "birch", "elm"}));
    }
