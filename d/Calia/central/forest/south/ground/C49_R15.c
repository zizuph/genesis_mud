//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C49_R15", ({0, 0, "C50_R15", "C50_R16",
        "C49_R16", "C48_R16", "C48_R15", 0}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
