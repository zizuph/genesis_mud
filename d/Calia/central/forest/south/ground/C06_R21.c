//Room type {t}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C06_R21", ({"C06_R20", "C07_R20", "C07_R21",
        "C07_R22", "C06_R22", 0, 0, 0}),
        ({"sycamore", "cedar", "elm", "birch"}), ({"thicket"}));
    }
