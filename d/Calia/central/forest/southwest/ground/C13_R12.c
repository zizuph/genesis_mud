//Room type {f}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C13_R12", ({"C13_R11", "C14_R11", "C14_R12",
        "C14_R13", "C13_R13", 0, "C12_R12", "C12_R11"}),
        ({"sycamore", "elm", "birch"}), ({"thicket"}));
    }
