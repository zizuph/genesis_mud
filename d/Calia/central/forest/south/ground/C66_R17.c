//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C66_R17", ({"C66_R16", "C67_R16", 0, 0, 0, 0,
        "C65_R17", "C65_R16"}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
