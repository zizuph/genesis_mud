//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C64_R17", ({"C64_R16", "C65_R16", "C65_R17",
        0, 0, "C63_R18", "C63_R17", "C63_R16"}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
