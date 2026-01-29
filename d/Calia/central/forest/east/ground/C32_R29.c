//Room type {M}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C32_R29", ({0, 0, "C33_R29", "C33_R30",
        "C32_R30", "C31_R30", "C31_R29", 0}),
        ({"fir", "beech", "elm"}), ({"thicket"}));
    }
