//Room type {M}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C37_R28", ({0, 0, 0, "C38_R29", "C37_R29",
        "C36_R29", "C36_R28", 0}),
        ({"fir", "beech", "elm"}), ({"thicket"}));
    }
