//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C21_R12", ({0, 0, "C22_R12", "C22_R13",
        "C21_R13", "C20_R13", 0, 0}),
        ({"balsam", "fir", "beech"}), ({"bog"}));
    }
