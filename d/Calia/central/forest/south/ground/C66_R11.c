//Room type {r}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C66_R11", ({0, 0, "C67_R11", "C67_R12",
        "C66_R12", "C65_R12", "C65_R11", 0}),
        ({"oak", "cedar", "elm"}), ({"rapids"}), ({"south"}));
    }
