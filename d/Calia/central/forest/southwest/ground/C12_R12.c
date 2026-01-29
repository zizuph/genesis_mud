//Room type {!}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C12_R12", ({"C12_R11", "C13_R11", "C13_R12",
        "C13_R13", 0, 0, 0, "C11_R11"}),
        ({"sycamore", "elm", "birch"}), ({"thicket"}),
        ({"northwest", "southeast"}));
    }
