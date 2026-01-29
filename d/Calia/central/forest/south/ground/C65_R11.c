//Room type {4}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C65_R11", ({0, 0, "C66_R11", "C66_R12",
        "C65_R12", "C64_R12", 0, 0}),
        ({"oak", "cedar", "elm"}), ({"thicket", "east", "rapids", "north"}));
    }
