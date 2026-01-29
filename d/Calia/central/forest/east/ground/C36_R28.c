//Room type {M}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C36_R28", ({0, 0, "C37_R28", "C37_R29",
        "C36_R29", "C35_R29", "C35_R28", "C35_R27"}),
        ({"fir", "beech", "elm"}), ({"thicket"}));
    }
