//Room type {k}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C32_R13", ({"C32_R12", "C33_R12", 0, 0, 0,
        "C31_R14", "C31_R13", "C31_R12"}),
        ({"cedar"}), ({"thicket", "south", "mountains", "west"}));
    }
