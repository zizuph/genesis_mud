//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C22_R12", ({0, "C23_R11", "C23_R12",
        "C23_R13", "C22_R13", "C21_R13", "C21_R12", 0}),
        ({"balsam", "fir", "beech"}), ({"bog"}));
    }
