//Room type {x}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C18_R17", ({"C18_R16", "C19_R16",
        "C19_R17", "C19_R18", "C18_R18", "C17_R18", "C17_R17", "C17_R16"}),
        ({"sycamore", "birch", "elm"}));
    }
