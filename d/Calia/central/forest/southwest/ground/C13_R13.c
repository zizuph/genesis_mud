//Room type {!}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C13_R13", ({"C13_R12", "C14_R12", "C14_R13",
        "C14_R14", "C13_R14", 0, 0, "C12_R12"}),
        ({"sycamore", "elm", "birch"}), ({"thicket"}),
        ({"northwest", "southeast"}));
    }
