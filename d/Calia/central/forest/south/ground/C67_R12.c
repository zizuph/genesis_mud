//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C67_R12", ({"C67_R11", 0, "C68_R12",
        "C68_R13", "C67_R13", "C66_R13", "C66_R12", "C66_R11"}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
