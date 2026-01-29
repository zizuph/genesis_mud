//Room type {s}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C68_R12", ({0, 0, 0, 0, "C68_R13", "C67_R13",
        "C67_R12", "C67_R11"}),
        ({"oak", "cedar", "elm"}), ({"thicket"}));
    }
