//Room type {a}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C52_R21", ({"C52_R20", "C53_R20", 0, 0, 0, 0,
        "C51_R21", "C51_R20"}),
        ({"oak", "birch", "cedar", "elm"}), ({"thicket"}));
    }
