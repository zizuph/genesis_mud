//Room type {a}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C49_R21", ({"C49_R20", "C50_R20", "C50_R21",
        0, "C49_R22", "C48_R22", "C48_R21", "C48_R20"}),
        ({"oak", "birch", "cedar", "elm"}), ({"thicket"}));
    }
