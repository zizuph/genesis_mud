//Room type {a}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C46_R24", ({"C46_R23", "C47_R23", 0, 0, 0, 0,
        "C45_R24", "C45_R23"}),
        ({"oak", "birch", "cedar", "elm"}), ({"thicket"}));
    }
