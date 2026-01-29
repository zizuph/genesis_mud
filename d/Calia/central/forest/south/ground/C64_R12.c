//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C64_R12", ({0, "C65_R11", "C65_R12",
        "C65_R13", "C64_R13", "C63_R13", "C63_R12", 0}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
