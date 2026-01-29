//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C65_R12", ({"C65_R11", "C66_R11", "C66_R12",
        "C66_R13", "C65_R13", "C64_R13", "C64_R12", 0}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
