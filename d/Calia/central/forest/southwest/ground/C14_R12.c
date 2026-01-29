//Room type {t}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C14_R12", ({"C14_R11", 0, "C15_R12",
        "C15_R13", "C14_R13", "C13_R13", "C13_R12", "C13_R11"}),
        ({"sycamore", "cedar", "elm", "birch"}), ({"thicket"}));
    }
