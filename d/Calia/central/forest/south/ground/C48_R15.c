//Room type {3}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C48_R15", ({0, 0, "C49_R15", "C49_R16",
        "C48_R16", "C47_R16", 0, 0}),
        ({"oak", "cedar", "elm"}),
        ({"thicket", "north", "mountains", "west"}));
    }
