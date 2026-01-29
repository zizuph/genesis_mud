//Room type {a}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C46_R23", ({"C46_R22", "C47_R22", "C47_R23",
        0, "C46_R24", "C45_R24", "C45_R23", "C45_R22"}),
        ({"oak", "birch", "cedar", "elm"}), ({"thicket"}));
    }
