//Room type {f}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C13_R14", ({"C13_R13", "C14_R13", "C14_R14",
        "C14_R15", 0, 0, 0, 0}),
        ({"sycamore", "elm", "birch"}), ({"thicket"}));
    }
