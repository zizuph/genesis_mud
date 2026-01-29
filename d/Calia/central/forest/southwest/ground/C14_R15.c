//Room type {f}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C14_R15", ({"C14_R14", "C15_R14", "C15_R15",
        "C15_R16", "C14_R16", 0, 0, "C13_R14"}),
        ({"sycamore", "elm", "birch"}), ({"thicket"}));
    }
