//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C65_R17", ({"C65_R16", "C66_R16", "C66_R17",
        0, 0, 0, "C64_R17", "C64_R16"}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
