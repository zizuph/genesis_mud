//Room type {a}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C53_R20", ({"C53_R19", "C54_R19", 0, 0, 0,
        "C52_R21", "C52_R20", "C52_R19"}),
        ({"oak", "birch", "cedar", "elm"}), ({"thicket"}));
    }
