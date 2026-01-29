//Room type {t}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C15_R12", ({0, 0, 0, "C16_R13", "C15_R13",
        "C14_R13", "C14_R12", "C14_R11"}),
        ({"sycamore", "cedar", "elm", "birch"}), ({"thicket"}));
    }
