//Room type {b}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C20_R13", ({0, "C21_R12", "C21_R13",
        "C21_R14", "C20_R14", "C19_R14", "C19_R13", 0}),
        ({"balsam", "fir", "beech"}), ({"bog"}));
    }
