//Room type {a}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C48_R23", ({"C48_R22", "C49_R22", 0, 0, 0, 0,
        "C47_R23", "C47_R22"}),
        ({"oak", "birch", "cedar", "elm"}), ({"thicket"}));
    }
