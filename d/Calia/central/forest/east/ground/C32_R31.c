//Room type {M}

inherit "/d/Calia/central/forest/baserooms/base_edge";

void create_room()
    {
    create_forest_edge("C32_R31", ({"C32_R30", "C33_R30", "C33_R31",
        0, 0, 0, "C31_R31", "C31_R30"}),
        ({"fir", "beech", "elm"}), ({"thicket"}));
    }
