//Room type {c}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C15_R26", ({"C15_R25", "C16_R25", "C16_R26",
        0, 0, 0, "C14_R26", "C14_R25"}),
        ({"oak", "birch"}), ({"thicket"}));
    }
