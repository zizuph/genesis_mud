//Room type {f}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C15_R17", ({"C15_R16", "C16_R16", "C16_R17",
        "C16_R18", "C15_R18", 0, "C14_R17", "C14_R16"}),
        ({"sycamore", "elm", "birch"}), ({"thicket"}));
    }
