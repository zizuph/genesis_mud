//Room type {;}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C53_R15", ({0, 0, "C54_R15", "C54_R16",
        "C53_R16", "C52_R16", "C52_R15", 0}),
        ({"oak", "cedar", "elm"}), ({"thicket"}), "east");
    }
