//Room type {c}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C20_R27", ({"C20_R26", "C21_R26", "C21_R27",
        0, 0, 0, "C19_R27", "C19_R26"}),
        ({"oak", "birch"}), ({"thicket"}));
    }
