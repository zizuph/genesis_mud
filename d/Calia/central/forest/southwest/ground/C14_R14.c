//Room type {!}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C14_R14", ({"C14_R13", "C15_R13", "C15_R14",
        "C15_R15", "C14_R15", 0, "C13_R14", "C13_R13"}),
        ({"sycamore", "elm", "birch"}), ({"thicket"}),
        ({"northwest", "southeast"}));
    }
