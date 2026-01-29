//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C55_R15", ({0, 0, "C56_R15", "C56_R16",
        "C55_R16", "C54_R16", "C54_R15", 0}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
