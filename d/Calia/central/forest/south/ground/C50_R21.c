//Room type {a}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C50_R21", ({"C50_R20", "C51_R20", "C51_R21",
        0, 0, "C49_R22", "C49_R21", "C49_R20"}),
        ({"oak", "birch", "cedar", "elm"}), ({"thicket"}));
    }
