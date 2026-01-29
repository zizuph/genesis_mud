//Room type {t}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C20_R15", ({0, 0, 0, "C21_R16", "C20_R16",
        "C19_R16", "C19_R15", "C19_R14"}),
        ({"sycamore", "cedar", "elm", "birch"}), ({"thicket"}));
    }
