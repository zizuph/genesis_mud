//Room type {:}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C50_R15", ({0, 0, "C51_R15", "C51_R16",
        "C50_R16", "C49_R16", "C49_R15", 0}),
        ({"oak", "cedar", "elm"}), ({"thicket"}), "west");
    }
