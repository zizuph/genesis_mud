//Room type {a}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C51_R21", ({"C51_R20", "C52_R20", "C52_R21",
        0, 0, 0, "C50_R21", "C50_R20"}),
        ({"oak", "birch", "cedar", "elm"}), ({"thicket"}));
    }
