//Room type {c}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C23_R27", ({"C23_R26", "C24_R26", "C24_R27",
        0, 0, 0, "C22_R27", "C22_R26"}),
        ({"oak", "birch"}), ({"thicket"}));
    }
