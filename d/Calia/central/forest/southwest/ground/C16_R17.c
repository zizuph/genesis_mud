//Room type {(}

inherit "/d/Calia/central/forest/baserooms/base_interior";

void create_room()
    {
    create_forest_interior("C16_R17", ({"C16_R16", "C17_R16",
        "C17_R17", "C17_R18", "C16_R18", "C15_R18", "C15_R17", "C15_R16"}),
        ({"sycamore", "birch", "elm"}), ({"north", "southeast"}));
    }
